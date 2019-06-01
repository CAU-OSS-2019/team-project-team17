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

UserInfo set_user(MYSQL_ROW input, UserInfo user) {
	strcpy(user.nickname , input[0]);
	strcpy(user.id , input[1]);
	strcpy(user.pwd , input[2]);
	

	return user;
}

void main()
{
	UserInfo user;

	MYSQL conn;
	MYSQL *connection = NULL;
	MYSQL_RES *sql_result;
	MYSQL_ROW sql_row;
	int query_state;

	char query[255];

	cout << "Sign In" << endl;

	cout << "id : ";
	cin >> user.id;

	cout << "password : ";
	cin >> user.pwd;

	mysql_init(&conn);

	connection = mysql_real_connect(&conn, HOST, USERNAME, PASSWORD, DBNAME, PORTNUM, NULL, 0);

	if (connection == NULL) {
		cout << "DB Not Connected : " << mysql_error(&conn) << endl;
		return;
	}

	sprintf(query, "SELECT * FROM login WHERE id='%s' AND pwd='%s'", user.id, user.pwd);

	query_state = mysql_query(connection, query);

	if (query_state != 0) {
		cout << "Login failed : " << mysql_error(&conn) << endl;
		mysql_close(&conn);
		return;
	}

	sql_result = mysql_store_result(connection);

	while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
		user = set_user(sql_row, user);
	}

	cout << "nickname\tid\tpassword" << endl;
	cout << user.nickname << "\t" << user.id << "\t" << user.pwd << endl;
	
	mysql_free_result(sql_result);

	mysql_close(&conn);

}