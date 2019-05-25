#ifndef __LOGIN_H__
#define __LOGIN_H__

#include "socket_server.h"

#include <mysql.h>

#define HOST "gamehaeduo-db.c8xdbny5rkis.ap-northeast-2.rds.amazonaws.com"
#define USERNAME "gamehaeduo"
#define PASSWORD "caugamehaeduo"
#define DBNAME "gamehaeduo"
#define PORTNUM 3306

using namespace std;

typedef struct UserInfo {
	
	string nickname;
	string id;
	string pwd;
	
}user_info;

class LogIn {
	private :

		// variables for login
		user_info user;

		MYSQL conn;
		MYSQL *connection = NULL;
		int query_state;
		char query[255];

		// variables for socket

	public :
		// Constructor


		user_info login(user_info input) {
			cout << "Log In" << endl;

			// Connect
			mysql_init(&conn);

			connection = mysql_real_connect(&conn, HOST, USERNAME, PASSWORD, DBNAME, PORTNUM, NULL, 0);

			if (connection == NULL) {
				cout << "DB Not Connected : " << mysql_error(&conn) << endl;
				return user;
			}

			// Query
			sprintf(query, "SELECT * FROM login WHERE id='%s' AND pwd='%s' LIMIT 1", input.id.c_str(), input.pwd.c_str());

			query_state = mysql_query(connection, query);
			if (query_state != 0) {
				cout << "Login failed : " << mysql_error(&conn) << endl;
				mysql_close(&conn);
				return user;
			}

			// Result
			sql_result = mysql_store_result(connection);
			while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
				user.nickname = sql_row[0];
				user.id = sql_row[1];
				user.pwd = sql_row[2];
			}	

			// Close
			mysql_free_result(sql_result);
			mysql_close(&conn);

			return user;
		}
}

#endif // __LOGIN_H__
