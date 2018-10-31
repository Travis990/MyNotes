#include "FastDFSClient.h"
#include "fdfs_client.h"
#include <stdexcept>
using namespace std;
namespace itcast
{
    FastDFSClient::FastDFSClient(string cfgFile)
        :mCfgFile(cfgFile)
    {
    }
    string FastDFSClient::upload(string fileName) throw(runtime_error)
    {
        char fileId[1024]={0};
        char group_name[FDFS_GROUP_NAME_MAX_LEN + 1];
        ConnectionInfo *pTrackerServer;

        int result=0;
        int store_path_index;
        ConnectionInfo storageServer;

        log_init();
        g_log_context.log_level = LOG_ERR;
        ignore_signal_pipe();

        if ((result=fdfs_client_init(this->mCfgFile.c_str())) != 0)
        {
            throw runtime_error("fdfs init fail with config file :"+ this->mCfgFile);
        }

        //从配置文件读取tracker的信息
        pTrackerServer = tracker_get_connection();
        if (pTrackerServer == NULL)
        {
            fdfs_client_destroy();
            throw runtime_error("fdfs tracker get coonnection fail");
        }

        *group_name = '\0';
        //通过tracker来查询可用的storage的信息
        if ((result=tracker_query_storage_store(pTrackerServer, \
                                                &storageServer, group_name, &store_path_index)) != 0)
        {
            fdfs_client_destroy();
            throw runtime_error("fdfs query storage server fail");
        }

        //使用相应的storage服务器上传文件
        //file_id直接写到传出参数里边
        result = storage_upload_by_filename1(pTrackerServer, \
                                             &storageServer, store_path_index, \
                                             fileName.c_str(), NULL, \
                                             NULL, 0, group_name, fileId);
        string retStr ;
        if (result == 0)
        {
            retStr = fileId;
        }
        else
        {
            throw runtime_error("fdfs update file fail , filename:"+fileName + " config file:" +this->mCfgFile);
        }

        //清理工作
        tracker_disconnect_server_ex(pTrackerServer, true);
        fdfs_client_destroy();
        return fileId;
    }
}
