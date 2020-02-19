#include "DataBaseConnection.h"



DataBaseConnection::DataBaseConnection()
{
	countdistinct = 0;
	userid = -1;
	step = 0;
}
void DataBaseConnection::Connect()
{
	// Получаем дескриптор соединения
	conn = mysql_init(NULL);
	if (conn == NULL)
	{
		// Если дескриптор не получен – выводим сообщение об ошибке
		fprintf(stderr, "Error: can'tcreate MySQL-descriptor\n");
		//exit(1); //Если используется оконное приложение
	}
	// Подключаемся к серверу
	if (!mysql_real_connect(conn, "185.26.122.49", "host6491_root", "R0oT", "host6491_test", NULL, NULL, 0))
	{
		// Если нет возможности установить соединение с сервером 
		// базы данных выводим сообщение об ошибке
		fprintf(stderr, "Error: can't connect to database: %s\n", mysql_error(conn));
	}
	else
	{
		// Если соединение успешно установлено выводим фразу - "Success!"
		fprintf(stdout, "Success!\n");
	}
}
bool DataBaseConnection::Authorization(std::string login,std::string pass)
{
	std::string query = "SELECT * FROM users WHERE email='" + login + "' and password='" + md5(pass) + "';";
	const char* q = query.c_str();
	qstate = mysql_query(conn, q);
	if (!qstate)
	{
		res = mysql_store_result(conn);
		
		while (row = mysql_fetch_row(res))
		{
			printf("ID: %s,nick: %s,email: %s, pass: %s , date: %s\n", row[0], row[1], row[2],row[3],row[4]);
			userid = atoi(row[0]);
			//vectordrum.push_back(row[4]);
		}
		SelectStep();
		return true;
	}
	else
	{
		std::cout << "Query failed:" << mysql_error(conn) << std::endl;
		return false;
	}
}
std::vector<std::string> DataBaseConnection::Query()
{
	//printf("step=%d\n", step);
	//printf("userid=%d\n", userid);
	if (userid == -1)
	{
		printf("You need autorization in system!\n");
		vectordrum.clear();
		std::string query = "SELECT * FROM drum where id=" + std::to_string(step)+";";
		const char* q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate)
		{
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
				vectordrum.push_back(row[2]);
			}
		}
		else
		{
			std::cout << "Query failed:" << mysql_error(conn) << std::endl;
		}
		return vectordrum;
	}
	CountDistinct();
	vectordrum.clear();
	std::string query = "SELECT * FROM drum where id="+std::to_string(step)+";";
	const char * q = query.c_str();
	qstate = mysql_query(conn, q);
	if (!qstate)
	{
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			//printf("ID: %s,Position: %s, Image: %s\n", row[0], row[1], row[2]);
			vectordrum.push_back(row[2]);
		}
	}
	else
	{
		std::cout << "Query failed:" << mysql_error(conn) << std::endl;
	}
	step++;
	if (step == countdistinct)
		step = 0;
	UpdateStep();
	return vectordrum;
}
void DataBaseConnection::CountDistinct()
{
	std::string  query = "SELECT count(distinct(id)) FROM drum;";
	const char* q = query.c_str();
	qstate = mysql_query(conn, q);
	if (!qstate)
	{
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			printf("row[0]: %s\n", row[0]);
			countdistinct = atoi(row[0]);
		}
	}
	else
	{
		std::cout << "Query failed:" << mysql_error(conn) << std::endl;
	}
	printf("countdistinct=%d\n", countdistinct);
}
void DataBaseConnection::SelectStep()
{
	std::string query = "SELECT step FROM users_data where users_id=" + std::to_string(userid) + ";";
	const char* q = query.c_str();
	qstate = mysql_query(conn, q);
	if (!qstate)
	{
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			//printf("ID: %s,Position: %s, Image: %s\n", row[0], row[1], row[2]);
			step = atoi(row[0]);
		}
	}
	else
	{
		std::cout << "Query failed:" << mysql_error(conn) << std::endl;
	}
}
void DataBaseConnection::UpdateStep()
{
	std::string query = "UPDATE users_data SET step=" + std::to_string(step) + ";";
	const char* q = query.c_str();
	qstate = mysql_query(conn, q);
	if (!qstate)
	{
		/*
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			//printf("ID: %s,Position: %s, Image: %s\n", row[0], row[1], row[2]);
		}
		*/
	}
	else
	{
		std::cout << "Query failed:" << mysql_error(conn) << std::endl;
	}
}
void DataBaseConnection::Close()
{
	// Закрываем соединение с сервером базы данных
	mysql_close(conn);
}
DataBaseConnection::~DataBaseConnection()
{
	vectordrum.clear();
}
