#include "DataBaseConnection.h"



DataBaseConnection::DataBaseConnection()
{
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
	// ������������ � �������
	if (!mysql_real_connect(conn, "127.0.0.1", "root", "root", "test", NULL, NULL, 0))
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
std::vector<std::string> DataBaseConnection::Query()
{
	vectordrum.clear();
	std::string query = "SELECT * FROM drum where id=0";
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
	return vectordrum;
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
