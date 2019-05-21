#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

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
	
	string nickname;
	string id;
	string pwd;
	
};

void main()
{	
	UserInfo user;

	MYSQL conn;
	MYSQL *connection = NULL;
	int query_state;

	char query[255];

	cout << "Sign Up" << endl;

	cout << "id : ";
	getline(cin, user.id);
	
	cout << "password : ";
	getline(cin, user.pwd);

	cout << "nickname : ";
	getline(cin, user.nickname);

	mysql_init(&conn);
	mysql_options(&conn, MYSQL_SET_CHARSET_NAME, "euckr");		//euckr
	mysql_options(&conn, MYSQL_INIT_COMMAND, "SET NAMES euckr");		// utf8
	
	connection = mysql_real_connect(&conn, HOST, USERNAME, PASSWORD, DBNAME, PORTNUM, NULL, 0);

	if (connection == NULL) {
		cout << "DB Not Connected : " << mysql_error(&conn) << endl;
		return;
	}

	sprintf(query, "INSERT INTO login VALUES ('%s', '%s', '%s')", user.nickname.c_str(), user.id.c_str(), user.pwd.c_str());

	query_state = mysql_query(connection, query);

	if (query_state != 0) {
		cout << "Insertion failed : " << mysql_error(&conn) << endl;
		mysql_close(&conn);
		return;
	}

	mysql_close(&conn);

}