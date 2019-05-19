#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <winsock2.h>
#include <mysql.h>

#pragma comment(lib, "libmysql.lib")

using namespace std;

#define hostname "gamehaeduo-db.c8xdbny5rkis.ap-northeast-2.rds.amazonaws.com"
#define username "gamehaeduo"
#define password "caugamehaeduo"a
#define dbname "gamehaeduo"
#define portnum 3306

void main()
{
	cout << "Start" << endl;
	cout << "MySQL client Version : " << mysql_get_client_info() << endl;

	MYSQL mysql;
	mysql_init(&mysql);

	if (!mysql_real_connect(&mysql, hostname, username, password, dbname, portnum, NULL, 0)) {
		cout << "DB Not Connected" << endl;
	}
	else {
		cout << "DB Connected" << endl;
	}
	mysql_close(&mysql);

}