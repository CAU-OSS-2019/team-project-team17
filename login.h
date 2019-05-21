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

/*
class SignUpSocketServer : public SocketServer {
	public :
		int receive_success;
		int send_success;
	
	public :
		SignupSocketServer(string socket_name, char server_ip[], int server_port)
			: SocketClient(socket_name, server_ip, server_port){

			this -> prepareServerSocket();
			
		}

		
}
*/

class LogIn {
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

		void set_user(MYSQL_ROW input) {
			user.nickname = input[0];
			user.id = input[1];
			user.pwd = input[2];
		}

	public :
		// Constructor

		
		// 로그인 후 아이디와 닉네임은 user.nickname, user.id로 사용하면 됨
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
				set_user(sql_row);
			}	

			// Close
			mysql_free_result(sql_result);
			mysql_close(&conn);

			return user;
		}
}

#endif // __LOGIN_H__
