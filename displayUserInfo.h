#ifndef __DISPLAYUSERINFO_H__
#define __DISPLAYUSERINFO_H__

#include "socket_server.h"

#include <mysql.h>

#define HOST "gamehaeduo-db.c8xdbny5rkis.ap-northeast-2.rds.amazonaws.com"
#define USERNAME "gamehaeduo"
#define PASSWORD "caugamehaeduo"
#define DBNAME "gamehaeduo"
#define PORTNUM 3306

using namespace std;

typedef struct UserGameInfo {

	string nickname;
	string rank;
	
}user_game_info;

class DisplayUserInfo {
	private :
		// variables for displayUserInfo
		user_game_info user;

		MYSQL conn;
		MYSQL *connection = NULL;
		int query_state;
		char query[255];
		
		// variables for socket

	public :
		// Constructor
		
		
		user_game_info displayUserInfo(string nickname) {
			cout << "Display User Info" << endl;

			// Connect
			mysql_init(&conn);

			connection = mysql_real_connect(&conn, HOST, USERNAME, PASSWORD, DBNAME, PORTNUM, NULL, 0);

			if (connection == NULL) {
				cout << "DB Not Connected : " << mysql_error(&conn) << endl;
				return user;
			}
			
			// Query
			sprintf(query, "SELECT nickname, rank FROM userEntireInfo WHERE nickname='%s' LIMIT 1", nickname.c_str());

			query_state = mysql_query(connection, query);

			if (query_state != 0) {
				cout << "Display User Info failed : " << mysql_error(&conn) << endl;
				mysql_close(&conn);
				return user;
			}

			// Result
			sql_result = mysql_store_result(connection);

			while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
				user.nickname = sql_row[0];
				user.rank = sql_row[1];
			}	

			// Close
			mysql_free_result(sql_result);
			mysql_close(&conn);

			return user;
		}
}

#endif // __DISPLAYUSERINFO_H__
