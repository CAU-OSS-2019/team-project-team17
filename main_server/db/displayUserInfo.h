#ifndef __DISPLAYUSERINFO_H__
#define __DISPLAYUSERINFO_H__

#include "socket_server.h"

#include </usr/include/mysql/mysql.h>

#define HOST "gamehaeduo-db.c8xdbny5rkis.ap-northeast-2.rds.amazonaws.com"
#define USERNAME "gamehaeduo"
#define PASSWORD "caugamehaeduo"
#define DBNAME "gamehaeduo"
#define PORTNUM 3306

using namespace std;

#include "../../structs/struct.h"

class DisplayUserInfo {
	private :
		// variables for displayUserInfo
		

		MYSQL conn;
		MYSQL *connection = NULL;
		int query_state;
		char query[255];
		MYSQL_RES *sql_result;
        MYSQL_ROW sql_row;
		// variables for socket

	public :
		// Constructor
		
		
		
		user_game_info displayUserInfo(string_key strkey) {

			user_game_info user;


			cout << "Display User Info" << endl;
			strcpy(user.nickname,"FAIL");
			strcpy(user.rank,"FAIL");
			

			// Connect
			mysql_init(&conn);
			mysql_options(&conn, MYSQL_SET_CHARSET_NAME, "utf8");		//euckr
			mysql_options(&conn, MYSQL_INIT_COMMAND, "SET NAMES utf8");


			connection = mysql_real_connect(&conn, HOST, USERNAME, PASSWORD, DBNAME, PORTNUM, NULL, 0);

			if (connection == NULL) {
				cout << "DB Not Connected : " << mysql_error(&conn) << endl;
				return user;
			}
			
			// Query
			cout<<"running QUERY get nickname"<<endl;
			sprintf(query, "SELECT nickname FROM login WHERE id='%s' LIMIT 1", strkey.str);

			query_state = mysql_query(connection, query);

			if (query_state != 0) {
				cout << "Display User Info failed : " << mysql_error(&conn) << endl;
				mysql_close(&conn);
				return user;
			}

			// Result
			sql_result = mysql_store_result(connection);

			while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
				strcpy(user.nickname, sql_row[0]);
			}

			cout<<"getnickname SUCCESS : "<<user.nickname<<endl;



			cout<<"running QUERY get rank"<<endl;
			sprintf(query, "SELECT rank FROM userEntireInfo WHERE nickname='%s' LIMIT 1", user.nickname);

			query_state = mysql_query(connection, query);

			if (query_state != 0) {
				cout << "Display User Info failed : " << mysql_error(&conn) << endl;
				mysql_close(&conn);
				return user;
			}

			// Result
			sql_result = mysql_store_result(connection);

			if ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
				strcpy(user.rank, sql_row[0]);
				cout<<"get rank SUCCESS: "<<user.rank<<endl;
			} else {
				cout<<"get rank failed"<<endl;
			}



			// Close
			mysql_free_result(sql_result);
			mysql_close(&conn);

			cout << "userdata return" << endl;


			return user;
		}
};

#endif // __DISPLAYUSERINFO_H__
