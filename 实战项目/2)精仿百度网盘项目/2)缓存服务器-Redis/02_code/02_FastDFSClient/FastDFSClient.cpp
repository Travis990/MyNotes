#include "FastDFSClient.h"
#include "fdfs_client.h"
#include "logger.h"
using namespace std;
namespace itcast
{
    FastDFSClient::FastDFSClient(string cfgFile)
        :mCfgFile(cfgFile)
    {
    }
    string FastDFSClient::upload(std::string localFile) throw(std::runtime_error) 
    {
        //完成完成，返回文件ID，有错抛出异常
        //1 初始化
        //char *conf_filename;
        //char *local_filename;
        char group_name[FDFS_GROUP_NAME_MAX_LEN + 1];
        ConnectionInfo *pTrackerServer;
        int result;
        int store_path_index;
        ConnectionInfo storageServer;
        char file_id[128];

        //传出参数
        string outFileId;

        log_init();
        g_log_context.log_level = LOG_ERR;
        ignore_signal_pipe();

        //2 读取配置文件
        if ((result=fdfs_client_init(mCfgFile.c_str())) != 0) //注意使用成员变量
        {
            throw runtime_error("fdfs_client_init fail");
        }

        try
        {
            //以下的异常抛出是要进行垃圾处理
            //连接tracker
            pTrackerServer = tracker_get_connection();
            if (pTrackerServer == NULL)
            {
                fdfs_client_destroy();
                throw runtime_error("tracker_get_connection fail");
            }

            *group_name = '\0';

            //通过tracker来查询哪台storage服务器可用
            if ((result=tracker_query_storage_store(pTrackerServer, \
                            &storageServer, group_name, &store_path_index)) != 0)
            {
                //错误处理
                fdfs_client_destroy();
                //fprintf(stderr, "tracker_query_storage fail, " \
                //        "error no: %d, error info: %s\n", \
                //        result, STRERROR(result));
                throw runtime_error("tracker_query_storage_store fail");
            }

            //上传本地文件到storage服务器
            //        //注意使用std::string localFile
            result = storage_upload_by_filename1(pTrackerServer, \
                    &storageServer, store_path_index, \
                    localFile.c_str(), NULL, \
                    NULL, 0, group_name, file_id);
            if (result == 0)
            {
                //printf("%s\n", file_id);
                //strcpy(out_file_id,file_id);
                outFileId = file_id;
            }
            else
            {
                //fprintf(stderr, "upload file fail, " \
                //        "error no: %d, error info: %s\n", \
                //        result, STRERROR(result));
                throw runtime_error("upload_file fail");
            }

        }
        catch(const exception &e)
        {
            // 清理垃圾
            tracker_disconnect_server_ex(pTrackerServer, true);
            fdfs_client_destroy();
            throw e;
        }
        // 清理垃圾
        tracker_disconnect_server_ex(pTrackerServer, true);
        fdfs_client_destroy();

        return outFileId;
    }
}
