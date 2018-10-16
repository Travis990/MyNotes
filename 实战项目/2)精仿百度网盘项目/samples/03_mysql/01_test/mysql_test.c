#include <mysql/mysql.h> //数据库
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* -------------------------------------------*/
/**
 * @brief  打印操作数据库出错时的错误信息
 *
 * @param conn       (in)    连接数据库的句柄
 * @param title      (int)   用户错误提示信息
 *
 */
/* -------------------------------------------*/
void print_error(MYSQL *conn, const char *title)
{
    fprintf(stderr,"%s:\nError %u (%s)\n", title, mysql_errno(conn), mysql_error(conn));
}

/* -------------------------------------------*/
/**
 * @brief  连接数据库
 *
 * @param user_name	 (in)   数据库用户
 * @param passwd     (in)   数据库密码
 * @param db_name    (in)   数据库名称
 *
 * @returns   
 *          成功：连接数据库的局部
 *			失败：NULL
 */
/* -------------------------------------------*/
MYSQL* msql_conn(char *user_name, char* passwd, char *db_name)
{
    MYSQL *conn = NULL; //MYSQL对象句柄
                  

	//用来分配或者初始化一个MYSQL对象，用于连接mysql服务端
    conn = mysql_init(NULL);
    if (conn == NULL) 
	{
        fprintf(stderr, "mysql 初始化失败\n");
        return NULL;
    }

	//mysql_real_connect()尝试与运行在主机上的MySQL数据库引擎建立连接
    //conn: 是已有MYSQL结构的地址。调用mysql_real_connect()之前，必须调用mysql_init()来初始化MYSQL结构。
	//NULL: 值必须是主机名或IP地址。如果值是NULL或字符串"localhost"，连接将被视为与本地主机的连接。
	//user_name: 用户的MySQL登录ID
	//passwd: 参数包含用户的密码
	if ( mysql_real_connect(conn, NULL, user_name, passwd, db_name, 0, NULL, 0) == NULL)
	{
        fprintf(stderr, "mysql_conn 失败:Error %u(%s)\n", mysql_errno(conn), mysql_error(conn));
		
        mysql_close(conn);
        return NULL;
    }

    return conn;
}


/* -------------------------------------------*/
/**
 * @brief  处理数据库查询结构
 *
 * @param conn	     (in)   连接数据库的句柄
 * @param res_set    (in)   数据库查询后的结果集
 *
 */
/* -------------------------------------------*/
void process_result_set(MYSQL *conn, MYSQL_RES *res_set)
{
    MYSQL_ROW row;
    uint i;

	// mysql_fetch_row从使用mysql_store_result得到的结果结构中提取一行，并把它放到一个行结构中。当数据用完或发生错误时返回NULL.
    while ((row = mysql_fetch_row(res_set)) != NULL)
	{

		//mysql_num_fields获取结果中列的个数
        for(i = 0; i < mysql_num_fields(res_set); i++)
		{
            if (i > 0)
			{
				fputc('\t',stdout);
			}
            printf("%s",row[i] != NULL ? row[i] : "NULL");
        }

        fputc('\n',stdout);
    }

    if( mysql_errno(conn) != 0 ) 
	{
        print_error(conn,"mysql_fetch_row() failed");
    }
    else 
	{
		//mysql_num_rows接受由mysql_store_result返回的结果结构集，并返回结构集中的行数 
        printf("%lu rows returned \n", (ulong)mysql_num_rows(res_set));
    }
}

int main()
{
	char buf[512] = {0};

	//连接数据库
    MYSQL *conn = msql_conn("root", "123456", "car");
    if (conn == NULL) 
	{
        return 1;
    }
	
	//这个很重要，设置数据库编码，否则，中文插入乱码
	mysql_query(conn, "set names utf8");
	
	 //插入
    sprintf(buf, "insert into %s (factory,name,price,sum, sell, last) values ('%s', '%s', '%d', '%d', '%d', '%d')",
            "brand", "一汽大众", "奥迪A6", 36, 50, 8, 42);
	
	//执行sql语句
	//函数接收参数连接句柄和字符串形式的有效SQL语句（没有结束的分号，这与mysql工具不同）。如果成功，它返回0。
    if ( mysql_query (conn, buf) != 0 ) 
	{
        print_error(conn, "插入失败");
    }
    else 
	{
        printf("插入成功,受影响行数:%lu\n",(ulong)mysql_affected_rows(conn));
    }
	
	//查询
    sprintf(buf, "select * from %s", "brand");
    if(mysql_query(conn, buf) != 0) //失败
	{
        print_error(conn,"mysql_query() error");
    }
	else
	{
        MYSQL_RES *res_set;
		//一次提取所有数据：mysql_store_result
		//它返回一个指向结果集结构的指针，如果失败返回NULL
        res_set = mysql_store_result(conn);

        if(res_set == NULL)
		{
			 print_error(conn,"mysql_store_result failed");
		}
           
        else 
		{
			//此为自定义函数，处理结果集
            process_result_set(conn,res_set);
			
			//完成所有对数据的操作后，调用mysql_free_result来善后处理
            mysql_free_result(res_set);
        }
    }
	
	// 关闭数据库连接
	mysql_close(conn);
	
	
	return 0;
}