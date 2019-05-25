#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <map>

#include <winsock2.h>
#include <mysql.h>


#pragma comment(lib, "libmysql.lib")

using namespace std;

#define HOST "gamehaeduo-db.c8xdbny5rkis.ap-northeast-2.rds.amazonaws.com"
#define USERNAME "gamehaeduo"
#define PASSWORD "caugamehaeduo"
#define DBNAME "gamehaeduo"
#define PORTNUM 3306


typedef struct BaseCharacterKey{
	string character_name;
	string rank;

	bool operator<(const BaseCharacterKey& k) const {

		if (character_name < k.character_name)
			return true;
		else if (character_name > k.character_name)
			return false;

		if (rank < k.rank)
			return true;
		else
			return false;
	}

}base_character_key;

 
//bool operator<(const BaseCharacterKey& t1, const BaseCharacterKey& t2) {
//
//	if (t1.character_name < t2.character_name)
//		return true;
//	else if (t1.character_name > t2.character_name)
//		return false;
//
//	if (t1.rank < t2.rank)
//		return true;
//	else
//		return false;
//}


void main()
{
	map<base_character_key, float> base_character_map;

	MYSQL conn;
	MYSQL *connection = NULL;
	MYSQL_RES *sql_result;
	MYSQL_ROW sql_row;
	int query_state;
	char query[255];

	mysql_init(&conn);

	connection = mysql_real_connect(&conn, HOST, USERNAME, PASSWORD, DBNAME, PORTNUM, NULL, 0);

	if (connection == NULL) {
		cout << "DB Not Connected : " << mysql_error(&conn) << endl;
		return;
	}

	sprintf(query, "SELECT * FROM baseCharacterInfo");

	query_state = mysql_query(connection, query);

	if (query_state != 0) {
		cout << "getting character information failed : " << mysql_error(&conn) << endl;
		mysql_close(&conn);
		return;
	}

	sql_result = mysql_store_result(connection);

	base_character_key bc_key;
	float win_rate;

	while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
		//set_base_character_info(sql_row);
		bc_key.character_name = sql_row[0];
		bc_key.rank = sql_row[1];
		win_rate = atof(sql_row[2]);

		base_character_map.insert(pair<base_character_key, float>(bc_key, win_rate));
	}

	mysql_free_result(sql_result);
	mysql_close(&conn);

	cout << "character_name\trank\twin_rate" << endl;
	
	for (auto iter=base_character_map.begin(); iter != base_character_map.end(); iter++) {
		cout << iter->first.character_name << "\t\t" << iter->first.rank << "\t" << iter->second << endl;
	}

}