#pragma once
#include <iostream>
#include <mysql.h>
#include <vector>
#pragma comment(lib,"mysqlcppconn.lib")
#pragma comment(lib,"libmysql.lib")
#include "MD5.h"
class DataBaseConnection
{
public:
	DataBaseConnection();
	void Connect();
	bool Authorization(std::string login, std::string pass);
	std::vector<std::string> Query();
	void Close();
	~DataBaseConnection();
	MYSQL *conn;
	MYSQL_ROW row;
	MYSQL_RES *res;
	int qstate;
	std::vector<std::string> vectordrum;
};

