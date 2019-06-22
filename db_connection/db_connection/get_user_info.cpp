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


typedef struct CharacterInfo {
	int wins;
	int losses;
	float kills;
	float deaths;
	float assist;
}character_info;

typedef struct UserCharacterInfo {
	string rank;
	float wins;
	float losses;
	map<string, character_info> character;

}user_character_info;


void main()
{
	user_character_info user_info;

	MYSQL conn;
	MYSQL *connection = NULL;
	MYSQL_RES *sql_result;
	MYSQL_ROW sql_row;
	int query_state;
	char query[255];

	string nickname;

	cout << "nickname : ";
	getline(cin, nickname);

	// Connect
	mysql_init(&conn);
	mysql_options(&conn, MYSQL_SET_CHARSET_NAME, "euckr");		//euckr
	mysql_options(&conn, MYSQL_INIT_COMMAND, "SET NAMES euckr");		// utf8

	connection = mysql_real_connect(&conn, HOST, USERNAME, PASSWORD, DBNAME, PORTNUM, NULL, 0);

	if (connection == NULL) {
		cout << "DB Not Connected : " << mysql_error(&conn) << endl;
		return;
	}

	// Query - userEntireInfo
	sprintf(query, "SELECT * FROM userEntireInfo WHERE nickname='%s' LIMIT 1", nickname);

	query_state = mysql_query(connection, query);

	if (query_state != 0) {
		cout << "getting user entire information failed : " << mysql_error(&conn) << endl;
		mysql_close(&conn);
		return;
	}

	// Result - userEntireInfo
	sql_result = mysql_store_result(connection);

	while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {

		user_info.rank = sql_row[1];
		user_info.wins = atof(sql_row[2]);
		user_info.losses = atof(sql_row[3]);
	}
	mysql_free_result(sql_result);


	// Query - userCharacterInfo
	sprintf(query, "SELECT * FROM userCharacterInfo WHERE nickname='%s'", nickname);

	query_state = mysql_query(connection, query);

	if (query_state != 0) {
		cout << "getting user character information failed : " << mysql_error(&conn) << endl;
		mysql_close(&conn);
		return;
	}

	// Result
	sql_result = mysql_store_result(connection);

	map<string, character_info> character_map;
	string ch_key;
	character_info ch_value;

	while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {

		ch_key = sql_row[2];
		ch_value.wins = atof(sql_row[3]);
		ch_value.losses = atof(sql_row[4]);
		ch_value.kills = atof(sql_row[5]);
		ch_value.deaths = atof(sql_row[6]);
		ch_value.assist = atof(sql_row[7]);

		character_map.insert(pair<string, character_info>(ch_key, ch_value));
	}

	if (character_map.size() > 0) {
		user_info.character.insert(character_map.begin(), character_map.end());
	}

	mysql_free_result(sql_result);
	mysql_close(&conn);

	cout << user_info.rank << "\t" << user_info.wins << "\t" << user_info.losses << endl;

	for (auto iter = user_info.character.begin(); iter != user_info.character.end(); iter++) {
		cout << iter->first << "\t" << iter->second.wins << "\t" << iter->second.losses << "\t" 
			<< iter->second.kills << "\t" << iter->second.deaths << "\t" << iter->second.assist << endl;
	}

}