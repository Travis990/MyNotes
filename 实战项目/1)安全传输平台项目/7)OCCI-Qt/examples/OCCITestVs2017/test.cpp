#include <iostream>
#include <occi.h>

using namespace std;
using namespace oracle::occi;  //命令空间

int main(void)
{
	unsigned int ret = -1;

	string name = "scott";
	string passwd = "11";
	string connectStr = "192.168.11.53:1521/orcl";

	//1. 创建OCCI的环境
	Environment *env = Environment::createEnvironment();
	if (NULL == env)
	{
		cout << "createEnvironment failed...." << endl;
		return 1;
	}

	//2. 连接数据库
	Connection *connect = env->createConnection(name, passwd, connectStr);
	if (NULL == connect)
	{
		cout << "CreateConnection failed..." << endl;
		return 1;
	}
	cout << "连接oracle服务端ok ..." << endl;

	//3. 创建一个Statement对象
	Statement *stat =  connect->createStatement();
	if (NULL == stat)
	{
		cout << "createStatement failed...." << endl;
		return 1;
	}

#if 0
	//4. 执行insert语句
	//ret = stat->executeUpdate("insert into dept values(3, '3name', '3loc')");
	//执行delete语句
	//ret = stat->executeUpdate("delete from dept where deptno = 3");
	//执行update语句
	ret = stat->executeUpdate("update dept set dname = '1name' where deptno = 1");
	if (ret <= 0)
	{
		cout << "executeUpdate failed...." << endl;
		return 1;
	}
#else
	//4. 执行查询
	ResultSet *resSet = stat->executeQuery("select deptno, dname, loc from dept");
	if (NULL == resSet)
	{
		cout << "executeQuery failed..." << endl;
		return 1;
	}

	//输出结果
	int id = 0;
	static string dname;
	static string loc;

	while (resSet->next())
	{
		//cout << "aaaaaaaaaaaaa" << endl;
		id = resSet->getInt(1);
		//cout << "aaaaaaaaaaaaa" << endl;
		//dname = resSet->getString(2);
		//cout << "aaaaaaaaaaaaa" << endl;
		//loc = resSet->getString(3);
		//cout << "aaaaaaaaaaaaa" << endl;

		cout << id << " " << dname << " " << loc << endl;
	}
	

	cout << "end................" << endl;
	//关闭结果集
	stat->closeResultSet(resSet);

#endif


	//事务相关处理
	string sql = "insert into dept values(:1, :2, :3)";
	stat->setSQL(sql);
	stat->setInt(1, 3);
	stat->setString(2, "3name");
	stat->setString(3, "3loc");

#if 0
	ret = stat->executeUpdate();
	if (0 == ret)
	{
		cout << "executeUpdate failed...." << endl;
		connect->rollback();
	}
	else
	{
		connect->commit();
	}
#else
	//设置事务为自动提交
	stat->setAutoCommit(true);
	ret = stat->executeUpdate();
	if (0 == ret)
	{
		cout << "executeUpdate failed...." << endl;
	}

#endif
	//关闭连接
	env->terminateConnection(connect);

	//终止环境
	Environment::terminateEnvironment(env);


	cout << "hello world" << endl;

	return 0;
}