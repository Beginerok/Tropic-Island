#pragma once
#include <iostream>
#include <mysql.h>
#include <vector>
#pragma comment(lib,"mysqlcppconn.lib")
#pragma comment(lib,"libmysql.lib")
class DataBaseConnection
{
public:
	DataBaseConnection();
	void Connect();
	std::vector<std::string> Query();
	void Close();
	~DataBaseConnection();
	MYSQL *conn;
	MYSQL_ROW row;
	MYSQL_RES *res;
	int qstate;
	std::vector<std::string> vectordrum;
};

