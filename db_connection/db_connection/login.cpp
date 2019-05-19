#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <winsock2.h>
#include <mysql.h>

#pragma comment(lib, "libmysql.lib")

using namespace std;

#define HOST "gamehaeduo-db.c8xdbny5rkis.ap-northeast-2.rds.amazonaws.com"
#define USERNAME "gamehaeduo"
#define PASSWORD "caugamehaeduo"
#define DBNAME "gamehaeduo"
#define PORTNUM 3306

struct UserInfo {
	
	char nickname[30];
	char id[30];
	char pwd[30];
	
};

void main()
{	
	UserInfo user;

	cout << "Start" << endl;
	cout << "MySQL client Version : " << mysql_get_client_info() << endl;

	cout << "id : ";
	cin >> user.id;
	
	cout << "password : ";
	cin >> user.pwd;

	cout << "nickname : ";
	cin >> user.nickname;

	MYSQL conn;
	MYSQL *connection = NULL;
	MYSQL_RES *res;
	MYSQL_ROW row;
	int query_state;

	char query[255];

	mysql_init(&conn);
	
	/*if (mysql_real_connect(&conn, HOST, USERNAME, PASSWORD, DBNAME, PORTNUM, NULL, 0)) {
		cout << "DB Connected" << endl;
	}
	else {
		cout << "DB Not Connected" << endl;
	}*/
	
	connection = mysql_real_connect(&conn, HOST, USERNAME, PASSWORD, DBNAME, PORTNUM, NULL, 0);

	if (connection == NULL) {
		cout << "DB Not Connected : " << mysql_error(&conn) << endl;
		return;
	}

	sprintf(query, "INSERT INTO login VALUES ('%s', '%s', '%s')", user.nickname, user.id, user.pwd);

	query_state = mysql_query(connection, query);

	if (query_state != 0) {
		cout << "Insertion failed" << endl;
		mysql_close(&conn);
		return;
	}




	mysql_close(&conn);

}