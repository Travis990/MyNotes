#include "redis_op.h"
#include "deal_mysql.h" //mysql
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*------------------------------------------.
| 个人用户文件列表表 (LIST)                 |
| Key:     FILE_USER_LIST_user              |
| value:  fileid                            |
| redis 语句                                |
|    lpush key value                        |
|    lrange key start stop                  |
`------------------------------------------*/
#define FILE_USER_LIST                   "FILE_USER_LIST_MIKE"

int main()
{
	int retn = 0;
	
	MYSQL *mysql_conn = NULL; //数据库连接句柄
	redisContext *redis_conn = NULL;
	
	//RVALUES为redis 表存放批量value字符串数组类型
    //typedef char (*RVALUES)[1024]
    RVALUES fileid_list_values = NULL;

	//===========mysql连接
    //连接 mysql 数据库
    mysql_conn = msql_conn("root", "123456", "sql_redis");
    if (mysql_conn == NULL)
    {
        printf("msql_conn connect err\n");
        retn = -1;
		goto END;
    }

    //设置数据库编码
    mysql_query(mysql_conn, "set names utf8");

	//=============redis连接
    redis_conn = rop_connectdb_nopwd("127.0.0.1", "6379");
    if (redis_conn == NULL)
    {
        printf("redis connected error\n");
        retn = -1;
		goto END;
    }
	
	char sql_cmd[512];

#if 0
	//数据库数据插入规则
	//1、mysql插入成功后
	//2、redis备份一份用户文件列表
	
	//第1条数据
	strcpy(sql_cmd, "insert into file_info (file_id, filename, user) values ('group1/M00/00/01/wKgfbVh2AGKASftLAAD-JOf3Vps147.jpg', '1.jpg', 'itcast')");
	
	if (mysql_query(mysql_conn, sql_cmd) != 0) //执行sql语句
    {
        print_error(mysql_conn, "插入失败");
		retn = -1;
		goto END;
    }
	
	rop_list_push(redis_conn, FILE_USER_LIST, "group1/M00/00/01/wKgfbVh2AGKASftLAAD-JOf3Vps147.jpg");
	
	//第2条数据
	strcpy(sql_cmd, "insert into file_info (file_id, filename, user) values ('group1/M00/00/01/wKgfbVhzLM2AQSGKAABHtjRwEY0951.jpg', '2.jpg', 'itcast')");
	
	if (mysql_query(mysql_conn, sql_cmd) != 0) //执行sql语句
    {
        print_error(mysql_conn, "插入失败");
		retn = -1;
		goto END;
    }
	
	rop_list_push(redis_conn, FILE_USER_LIST, "group1/M00/00/01/wKgfbVhzLM2AQSGKAABHtjRwEY0951.jpg");
	
	//第3条数据
	strcpy(sql_cmd, "insert into file_info (file_id, filename, user) values ('group1/M00/00/01/wKgfbVhzppyAJQfcAACA0qRB_do611.jpg', '3.jpg', 'itcast')");
	
	if (mysql_query(mysql_conn, sql_cmd) != 0) //执行sql语句
    {
        print_error(mysql_conn, "插入失败");
		retn = -1;
		goto END;
    }
	
	rop_list_push(redis_conn, FILE_USER_LIST, "group1/M00/00/01/wKgfbVhzppyAJQfcAACA0qRB_do611.jpg");
	
#endif	
	
	//数据库数据查询规则
    //1、数据先从redis中查询
    //2、如果redis中没有此数据，则再中mysql中查询，同时给redis备份
    //3、如果mysql也没有此数据，说明，数据库没有保存此数据
	
	//有3条数据，每条数据长度为1024
	fileid_list_values = (RVALUES)malloc(3*1024);
	
	int value_num; //元素个数
	
	//获取列表内容，范围为0~2
	retn = rop_range_list(redis_conn, FILE_USER_LIST, 0, 2, fileid_list_values, &value_num);
    if (retn < 0) //如果没有数据，从mysql中取数据
	{
		//list数据去重
        //得到链表中元素的个数，列表有数据
        if( rop_get_list_cnt(redis_conn, FILE_USER_LIST) > 0)
        {
            goto END;
        }
		
		strcpy(sql_cmd, "select file_id from file_info where user = 'itcast'"); //sql语句
		
		if (mysql_query(mysql_conn, sql_cmd) != 0)
        {
            printf("mysql_query err\n");
            goto END;
        }

        MYSQL_RES *res_set;
        res_set = mysql_store_result(mysql_conn);/*生成结果集*/
        if (res_set == NULL)
        {
            goto END;
        }

        MYSQL_ROW row;
        uint i;

        if (mysql_errno(mysql_conn) != 0)
        {
           printf("mysql_fetch_row() failed\n");
            goto END;
        }

        //mysql_fetch_row从使用mysql_store_result得到的结果结构中提取一行，并把它放到一个行结构中。
		//当数据用完或发生错误时返回NULL
        while ((row = mysql_fetch_row(res_set)) != NULL)
        {

            //mysql_num_fields获取结果中列的个数
            for(i = 0; i < mysql_num_fields(res_set); i++)
            {
                if(row[i] != NULL)
                {
                    rop_list_push(redis_conn, FILE_USER_LIST, row[i]);
					printf("rop_list_push(%s, %s)\n", FILE_USER_LIST, row[i]);
                }
            }
        }
		
		//重新从缓存读取数据
		retn = rop_range_list(redis_conn, FILE_USER_LIST, 0, 2, fileid_list_values, &value_num);
        if (retn < 0)
        {
            printf("redis range %s error", FILE_USER_LIST);
            goto END;
        }
	}
	
	//打印数据
	int i = 0;
	for (i = 0; i < value_num; i++)
	{
		printf("fileid_list_values[%d] = %s\n", i, fileid_list_values[i]);
	}
	
END:	
	if(redis_conn != NULL)
    {
        rop_disconnect(redis_conn);
    }

    if (mysql_conn != NULL)
    {
        mysql_close(mysql_conn); //断开数据库连接
    }
	
	if(fileid_list_values != NULL)
	{
		free(fileid_list_values);
	}

	return retn;
}
