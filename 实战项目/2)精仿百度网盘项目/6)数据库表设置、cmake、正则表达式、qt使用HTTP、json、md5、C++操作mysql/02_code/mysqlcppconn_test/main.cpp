#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#define DEFAULT_URI "tcp://127.0.0.1"
#define EXAMPLE_USER "root"
#define EXAMPLE_PASS "123456"
#define EXAMPLE_DB "test"

using namespace std;

int main()
{
    try {
        //1获取mysql驱动
        sql::Driver * driver = ::get_driver_instance();
        /* Using the Driver to create a connection */

        //2建立连接
        sql::Connection *con=driver->connect("127.0.0.1", "root", "123456");
        con->setSchema("cloud_disk");

        //3正常执行sql
        sql::Statement *stmt=con->createStatement();
        sql::ResultSet *res=
            stmt->executeQuery("SELECT * from user");

        //4返回结果查看
        while (res->next())
        {
            cout<<"Get User name:"<<res->getString("name")<<endl;
            cout<<"Get User id:"<<res->getInt64("id")<<endl;
            cout<<"Get User passwd:"<<res->getString("password")<<endl;
            cout<<"Get User phone:"<<res->getString("phone")<<endl;
        }
        delete res;
        delete stmt;
        delete con;

    }
    catch (sql::SQLException &e)
    {
        cerr<<"Get Exception :"<<e.what()<<endl;
    }
    cout << endl;
    cout << "... find more at http://www.mysql.com" << endl;
    cout << endl;
    return EXIT_SUCCESS;
}

