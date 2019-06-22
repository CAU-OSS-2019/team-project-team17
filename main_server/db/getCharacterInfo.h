#ifndef __GETCHARACTERINFO_H__
#define __GETCHARACTERINFO_H__

#include "socket_server.h"
#include "../../structs/struct.h"
#include </usr/include/mysql/mysql.h>
#include <map>

#define HOST "gamehaeduo-db.c8xdbny5rkis.ap-northeast-2.rds.amazonaws.com"
#define USERNAME "gamehaeduo"
#define PASSWORD "caugamehaeduo"
#define DBNAME "gamehaeduo"
#define PORTNUM 3306

using namespace std;



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
//		return false;s
//}



class GetCharacterInfo {
	private :

		
		MYSQL conn;
		MYSQL *connection = NULL;
		int query_state;
		char query[255];
		MYSQL_RES *sql_result;
		MYSQL_ROW sql_row;
		
		// variables for socket


	public :

		// variables for getCharacterInfo
		map<base_character_key, float> base_character_map;
		map<best_pick_key, best_pick_value> best_pick_map;
		
		// Constructor
		GetCharacterInfo(){
			base_character_map = getBaseCharacterInfo();
			best_pick_map = getBestPickCharacter();
		}	

		
		map<base_character_key, float> getBaseCharacterInfo();
		map<best_pick_key, best_pick_value> getBestPickCharacter();
/*
		map<base_character_key, float> getBaseCharacterInfo() {
			cout << "Get Base Character Information" << endl;

			// Connect
			mysql_init(&conn);

			connection = mysql_real_connect(&conn, HOST, USERNAME, PASSWORD, DBNAME, PORTNUM, NULL, 0);

			if (connection == NULL) {
				cout << "DB Not Connected : " << mysql_error(&conn) << endl;
				return base_character_map;
			}

			// Query
			sprintf(query, "SELECT * FROM baseCharacterInfo");

			query_state = mysql_query(connection, query);

			if (query_state != 0) {
				cout << "getting character information failed : " << mysql_error(&conn) << endl;
				mysql_close(&conn);
				return base_character_map;
			}

			// Result
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

			// Close
			mysql_free_result(sql_result);
			mysql_close(&conn);

			return base_character_map;
		}
*/	
	/*	
		map<best_pick_key, best_pick_value> getBestPickCharacter() {
			cout << "Get Best Pick Character Information" << endl;

			// Connect
			mysql_init(&conn);
			mysql_options(&conn, MYSQL_SET_CHARSET_NAME, "euckr");		//euckr
			mysql_options(&conn, MYSQL_INIT_COMMAND, "SET NAMES euckr");

			connection = mysql_real_connect(&conn, HOST, USERNAME, PASSWORD, DBNAME, PORTNUM, NULL, 0);

			if (connection == NULL) {
				cout << "DB Not Connected : " << mysql_error(&conn) << endl;
				return best_pick_map;
			}

			// Query
			sprintf(query, "SELECT * FROM bestPickCharacter");

			query_state = mysql_query(connection, query);

			if (query_state != 0) {
				cout << "getting best character information failed : " << mysql_error(&conn) << endl;
				mysql_close(&conn);
				return best_pick_map;
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

			// Close
			mysql_free_result(sql_result);
			mysql_close(&conn);

			return best_pick_map;
		}
*/

};

#endif // __GETCHARACTERINFO_H__
