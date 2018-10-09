/**
* Copyright (C) 2008 Happy Fish / YuQing
*
* FastDFS may be copied only under the terms of the GNU General
* Public License V3, which may be found in the FastDFS source kit.
* Please visit the FastDFS Home Page http://www.csource.org/ for more detail.
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "fdfs_client.h"
#include "logger.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int my_upload(const char *conf_filename ,const char *local_filename , char *out_file_id)
{
    //1 初始化
	//char *conf_filename;
	//char *local_filename;
	char group_name[FDFS_GROUP_NAME_MAX_LEN + 1];
	ConnectionInfo *pTrackerServer;
	int result;
	int store_path_index;
	ConnectionInfo storageServer;
	char file_id[128];

	log_init();
	g_log_context.log_level = LOG_ERR;
	ignore_signal_pipe();

    //2 读取配置文件
	if ((result=fdfs_client_init(conf_filename)) != 0)
	{
		return result;
	}

    //连接tracker
	pTrackerServer = tracker_get_connection();
	if (pTrackerServer == NULL)
	{
		fdfs_client_destroy();
		return errno != 0 ? errno : ECONNREFUSED;
	}

	*group_name = '\0';

    //通过tracker来查询哪台storage服务器可用
	if ((result=tracker_query_storage_store(pTrackerServer, \
	                &storageServer, group_name, &store_path_index)) != 0)
	{
        //错误处理
		fdfs_client_destroy();
		fprintf(stderr, "tracker_query_storage fail, " \
			"error no: %d, error info: %s\n", \
			result, STRERROR(result));
		return result;
	}

    //上传本地文件到storage服务器
	result = storage_upload_by_filename1(pTrackerServer, \
			&storageServer, store_path_index, \
			local_filename, NULL, \
			NULL, 0, group_name, file_id);
	if (result == 0)
	{
		//printf("%s\n", file_id);
        strcpy(out_file_id,file_id);
	}
	else
	{
		fprintf(stderr, "upload file fail, " \
			"error no: %d, error info: %s\n", \
			result, STRERROR(result));
	}

    // 清理垃圾
	tracker_disconnect_server_ex(pTrackerServer, true);
	fdfs_client_destroy();

	return result;
}
//使用execlp来上传文件
int my_upload2(const char *conf_filename ,const char *local_filename , char *out_file_id)
{
    //    1 创建一对管道 pipe
    int fd[2];
    int ret = pipe(fd);
    if(ret<0)
    {
        perror("pipe");
        return -1;
    }
    //2 创建子进程 fork
    ret = fork();
    if(ret==0)
    {
        //1 子进程
        //关闭读管道
        close(fd[0]);
        //
        ret = dup2(fd[1],STDOUT_FILENO);
        if(ret<0)
        {
            perror("dup2");
            close(fd[1]);
            exit(-1);
        }
        //变身 execlp  fdfs_upload_file 
        execlp("fdfs_upload_file","fdfs_upload_file",conf_filename,
                local_filename,NULL);
        //失败的情况下代码会走到这里
        perror("execlp");
        close(fd[1]);
        exit(-1);
    }
    else if(ret>0)
    {
        //2 父进程
        //关闭写管道
        close(fd[1]);

        //从读管道读取数据
        char buf[128]={0};
        ret = read(fd[0],buf,sizeof(buf));

        //返回值>0 ，读取成功
        //<0  ,出错
        //=0  ,对端关闭文件描述符
        
        //关闭读管道
        close(fd[0]);

        //帮子进程收尸 wait
        wait(NULL);

        if(ret<=0)
        {
            //错误处理
            return -1;
        }
        strcpy(out_file_id,buf);

        return 0;
    }
    else
    {
        //3 错误处理
        //返回错误
        perror("fork");
        return -1;
    }
}

int main(int argc, char *argv[])
{
    char conf_filename[] = "/etc/fdfs/client.conf";
    char local_filename[] = "./main.c";
    char out_file_id1[128]={0}; 
    char out_file_id2[128]={0}; 
    int ret = my_upload(conf_filename,local_filename,out_file_id1);
    if(ret!=0)
    {
        fprintf(stderr,"my_upload fail\n");
    }
    printf("get file id 1 : %s\n",out_file_id1);

    ret = my_upload2(conf_filename,local_filename,out_file_id2);
    if(ret!=0)
    {
        fprintf(stderr,"my_upload2 fail\n");
    }
    printf("get file id 2 : %s\n",out_file_id2);
    return 0;
}
