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

static void usage(char *argv[])
{
	printf("Usage: %s <config_file> <local_filename> " \
		"[storage_ip:port] [store_path_index]\n", argv[0]);
}

int main(int argc, char *argv[])
{
	char *conf_filename;
	char *local_filename;
	char group_name[FDFS_GROUP_NAME_MAX_LEN + 1];
	ConnectionInfo *pTrackerServer;
	int result;
	int store_path_index;
	ConnectionInfo storageServer;
	char file_id[128];
	
	if (argc < 3)
	{
		usage(argv);
		return 1;
	}

	log_init();	//初始化日志
	g_log_context.log_level = LOG_ERR;//日志级别
	ignore_signal_pipe(); //忽略某些信号和管道

	//根据配置文件初始化客户端
	//可以在配置文件中得到tracker、storage的信息
	conf_filename = argv[1];
	if ((result=fdfs_client_init(conf_filename)) != 0) 
	{
		return result;
	}

	//和tracker建立链接，成功返回tracker服务句柄
	pTrackerServer = tracker_get_connection();
	if (pTrackerServer == NULL)//失败
	{
		fdfs_client_destroy();//销毁
		return errno != 0 ? errno : ECONNREFUSED;
	}

	local_filename = argv[2];
	*group_name = '\0';
	if (argc >= 4)//参数大于4，指定一些端口，这里用不上
	{
		const char *pPort;
		const char *pIpAndPort;

		pIpAndPort = argv[3];
		pPort = strchr(pIpAndPort, ':');
		if (pPort == NULL)
		{
			fdfs_client_destroy();
			fprintf(stderr, "invalid storage ip address and " \
				"port: %s\n", pIpAndPort);
			usage(argv);
			return 1;
		}

		storageServer.sock = -1;
		snprintf(storageServer.ip_addr, sizeof(storageServer.ip_addr), \
			 "%.*s", (int)(pPort - pIpAndPort), pIpAndPort);
		storageServer.port = atoi(pPort + 1);
		if (argc >= 5)
		{
			store_path_index = atoi(argv[4]);
		}
		else
		{
			store_path_index = -1;
		}
	}
	//通过tracker服务句柄得到storage服务句柄，同时得到storage属于哪个组
	else if ((result=tracker_query_storage_store(pTrackerServer, \
	                &storageServer, group_name, &store_path_index)) != 0)
	{
		fdfs_client_destroy();
		fprintf(stderr, "tracker_query_storage fail, " \
			"error no: %d, error info: %s\n", \
			result, STRERROR(result));
		return result;
	}

	//上传文件，上传成功的话，file_id返回的是上传成功后文件的名字
	result = storage_upload_by_filename1(pTrackerServer, \
			&storageServer, store_path_index, \
			local_filename, NULL, \
			NULL, 0, group_name, file_id);
	if (result == 0)
	{
		printf("%s\n", file_id);
	}
	else
	{
		fprintf(stderr, "upload file fail, " \
			"error no: %d, error info: %s\n", \
			result, STRERROR(result));
	}

	//断开连接，释放资源
	tracker_disconnect_server_ex(pTrackerServer, true);
	fdfs_client_destroy();

	return result;
}

