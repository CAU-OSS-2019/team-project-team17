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


typedef struct BestPickKey {
	string character_name;
	string rank;
	string best_character;

	bool operator<(const BestPickKey& k) const{

		if (character_name < k.character_name)
			return true;
		else if (character_name > k.character_name)
			return false;

		if (rank < k.rank)
			return true;
		else if (rank > k.rank)
			return false;

		if (best_character < k.best_character)
			return true;
		else
			return false;
	}

}best_pick_key;

//bool operator<(const BestPickKey& t1, const BestPickKey& t2) {
//
//	if (t1.character_name < t2.character_name)
//		return true;
//	else if (t1.character_name > t2.character_name)
//		return false;
//
//	if (t1.rank < t2.rank)
//		return true;
//	else if (t1.rank > t2.rank)
//		return false;
//
//	if (t1.best_character < t2.best_character)
//		return true;
//	else
//		return false;
//}

typedef struct BestPickValue {
	float win_rate;
	string description;

	/*bool operator < (const BestPickValue& k) {
		if (win_rate < k.win_rate)
			return true;
		else if (win_rate > k.win_rate)
			return false;

		if (description < k.description)
			return true;
		else
			return false;
	}

	bool operator > (const BestPickValue& k) {
		if (win_rate < k.win_rate)
			return true;
		else if (win_rate > k.win_rate)
			return false;

		if (description < k.description)
			return true;
		else
			return false;
	}*/
}best_pick_value;

//bool operator>(const BestPickValue& t1, const BestPickValue& t2) {
//
//	if (t1.win_rate < t2.win_rate)
//		return true;
//	else if (t1.win_rate > t2.win_rate)
//		return false;
//
//	if (t1.description < t2.description)
//		return true;
//	else if (t1.description > t2.description)
//		return false;
//}


void main()
{
	map<best_pick_key, best_pick_value> best_pick_map;

	MYSQL conn;
	MYSQL *connection = NULL;
	MYSQL_RES *sql_result;
	MYSQL_ROW sql_row;
	int query_state;
	char query[255];

	mysql_init(&conn);
	mysql_options(&conn, MYSQL_SET_CHARSET_NAME, "euckr");		//euckr
	mysql_options(&conn, MYSQL_INIT_COMMAND, "SET NAMES euckr");

	connection = mysql_real_connect(&conn, HOST, USERNAME, PASSWORD, DBNAME, PORTNUM, NULL, 0);

	if (connection == NULL) {
		cout << "DB Not Connected : " << mysql_error(&conn) << endl;
		return;
	}

	// Query
	sprintf(query, "SELECT * FROM bestPickCharacter");

	query_state = mysql_query(connection, query);

	if (query_state != 0) {
		cout << "getting best character information failed : " << mysql_error(&conn) << endl;
		mysql_close(&conn);
		return;
	}

	// Result
	sql_result = mysql_store_result(connection);
	best_pick_key bp_key;
	best_pick_value bp_value;

	while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
		//set_base_character_info(sql_row);
		bp_key.character_name = sql_row[0];
		bp_key.rank = sql_row[1];
		bp_key.best_character = sql_row[2];
		bp_value.win_rate = atof(sql_row[3]);
		bp_value.description = sql_row[4];

		best_pick_map.insert(pair<best_pick_key, best_pick_value>(bp_key, bp_value));
	}

	mysql_free_result(sql_result);
	mysql_close(&conn);

	for (auto iter = best_pick_map.begin(); iter != best_pick_map.end(); iter++) {
		cout << iter->first.character_name << "\t" << iter->first.rank << "\t" << iter->first.best_character;
		cout << iter->second.win_rate << "\t" << iter->second.description << endl;
	}
	

}