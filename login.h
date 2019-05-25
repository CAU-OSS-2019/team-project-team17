#ifndef __LOGIN_H__
#define __LOGIN_H__

#include "socket_server.h"

#include </usr/include/mysql/mysql.h>

#define HOST "gamehaeduo-db.c8xdbny5rkis.ap-northeast-2.rds.amazonaws.com"
#define USERNAME "gamehaeduo"
#define PASSWORD "caugamehaeduo"
#define DBNAME "gamehaeduo"
#define PORTNUM 3306

using namespace std;

typedef struct UserInfo {
	string id;
	string pwd;
	
}user_info;


class Login {
	private :

		// variables for login
		user_info user;

		MYSQL conn;
		MYSQL *connection = NULL;
		int query_state;
		char query[255];

		// variables for socket
		int running_state = false;
		SignUpSocketServer *signupSocket_p;

		Login(void){
			user.id = NULL;
			cout << "user.id : " << user.id << endl;

			user.pwd = NULL;
			cout << "user.pwd : " <<user.pwd <<endl;
		}

		void connect_db(void) {
			mysql_init(&conn);

			connection = mysql_real_connect(&conn, HOST, USERNAME, PASSWORD, DBNAME, PORTNUM, NULL, 0);

			if (connection == NULL) {
				cout << "DB Not Connected : " << mysql_error(&conn) << endl;
				return;
			}
		}

		void set_user(MYSQL_ROW input) {
			user.id = input[0];
			user.pwd = input[1];
		}

	public :
		// Constructor

		
		// 로그인 후 아이디와 닉네임은 user.nickname, user.id로 사용하면 됨
		bool login(user_info input) {
			cout << "Log In" << endl;

			connect_db();

			sprintf(query, "SELECT * FROM login WHERE id='%s' AND pwd='%s' LIMIT 1", input.id.c_str(), input.pwd.c_str());

			query_state = mysql_query(connection, query);

			if (query_state != 0) {
				cout << "Login failed : " << mysql_error(&conn) << endl;
				mysql_close(&conn);
				return false;
			}

			sql_result = mysql_store_result(connection);

			while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
				
				set_user(sql_row);
			}	

			mysql_free_result(sql_result);
			mysql_close(&conn);

			return true;
		}
}

#endif // __LOGIN_H__
