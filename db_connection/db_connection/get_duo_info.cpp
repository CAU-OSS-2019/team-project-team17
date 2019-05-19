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

struct DuoInfo {

	char nickname[30];
	char rank[30];
	int wins;
	int losses;
	/*char wins[10];
	char losses[10];*/

};

void main()
{
	DuoInfo duo;

	MYSQL conn;
	MYSQL *connection = NULL;
	MYSQL_RES *sql_result;
	MYSQL_ROW sql_row;
	int query_state;

	char query[255];

	cout << "Get Duo Information" << endl;

	cout << "Duo Nickname : ";
	cin >> duo.nickname;

	mysql_init(&conn);

	connection = mysql_real_connect(&conn, HOST, USERNAME, PASSWORD, DBNAME, PORTNUM, NULL, 0);

	if (connection == NULL) {
		cout << "DB Not Connected : " << mysql_error(&conn) << endl;
		return;
	}

	sprintf(query, "SELECT * FROM userEntireInfo WHERE nickname='%s'", duo.nickname);

	query_state = mysql_query(connection, query);

	if (query_state != 0) {
		cout << "Getting Duo Information failed : " << mysql_error(&conn) << endl;
		mysql_close(&conn);
		return;
	}

	sql_result = mysql_store_result(connection);

	while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {

		strcpy(duo.nickname, sql_row[0]);
		strcpy(duo.rank, sql_row[1]);
		/*strcpy(duo.wins, sql_row[2]);
		strcpy(duo.losses, sql_row[3]);*/
		duo.wins = atoi(sql_row[2]);
		duo.losses = atoi(sql_row[3]);
	}

	cout << "nickname : ";
	cout << duo.nickname << endl;

	cout << "rank : ";
	cout << duo.rank << endl;

	cout << "wins : ";
	cout << duo.wins << endl;

	cout << "losses : ";
	cout << duo.losses << endl;

	mysql_free_result(sql_result);

	mysql_close(&conn);

}