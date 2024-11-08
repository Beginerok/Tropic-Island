#include "DataBaseConnection.h"

#include <fstream>


DataBaseConnection::DataBaseConnection()
{
	countdistinct = 0;
	userid = -1;
	step = 0;
	pointscredits = 0;
}
void DataBaseConnection::Connect()
{
	// �������� ���������� ����������
	conn = mysql_init(NULL);
	if (conn == NULL)
	{
		// ���� ���������� �� ������� � ������� ��������� �� ������
		fprintf(stderr, "Error: can'tcreate MySQL-descriptor\n");
		//exit(1); //���� ������������ ������� ����������
	}
	std::string line,ip,user,pass,db;
	std::ifstream file_settings("settings.txt");
	if (file_settings.is_open())
	{
		getline(file_settings, ip);
		getline(file_settings, user);
		getline(file_settings, pass);
		getline(file_settings, db);
	}
	file_settings.close();     // ��������� ����

	// ������������ � �������
	if (!mysql_real_connect(conn, ip.c_str(),user.c_str(),pass.c_str(),db.c_str(), NULL, NULL, 0))
	{
		// ���� ��� ����������� ���������� ���������� � �������� 
		// ���� ������ ������� ��������� �� ������
		fprintf(stderr, "Error: can't connect to database: %s\n", mysql_error(conn));
	}
	else
	{
		// ���� ���������� ������� ����������� ������� ����� - "Success!"
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
		int max_ = 6, min_ = 0;
		srand(time(NULL));
		std::string* drum = new std::string[max_ + 1];
		drum[0] = "auto1";
		drum[1] = "auto2";
		drum[2] = "auto3";
		drum[3] = "auto4";
		drum[4] = "auto5";
		drum[5] = "bonus";
		drum[6] = "wild";
		int num = -1;
		for (int i = 0; i < 30; i++)
		{
			num = min_ + rand() % (max_ - min_ + 1);
			vectordrum.push_back(drum[num]);
		}
		drum->clear();
		return vectordrum;//new
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
	std::string query = "UPDATE users_data SET step=" + std::to_string(step) + " where users_id=" + std::to_string(userid) + ";";
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
int DataBaseConnection::GetCredits()
{
	std::string query = "SELECT points FROM users_data where users_id=" + std::to_string(userid) + ";";
	const char* q = query.c_str();
	qstate = mysql_query(conn, q);
	if (!qstate)
	{
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			//printf("ID: %s,Position: %s, Image: %s\n", row[0], row[1], row[2]);
			pointscredits = atoi(row[0]);
		}
	}
	else
	{
		std::cout << "Query failed:" << mysql_error(conn) << std::endl;
	}
	return pointscredits;
}
void DataBaseConnection::SetCredits(int pointscredits_)
{
	std::string query = "UPDATE users_data SET points=" + std::to_string(pointscredits_) + " where users_id="+std::to_string(userid)+";";
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
	// ��������� ���������� � �������� ���� ������
	mysql_close(conn);
}
DataBaseConnection::~DataBaseConnection()
{
	vectordrum.clear();
}
