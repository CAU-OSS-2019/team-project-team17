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

typedef UserInfo {
	
	char nickname[30];
	char id[30];
	char pwd[30];
	
}user_info;

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

class SignUp {
	private :
		// data needed for signup
		user_info user;
		
		MYSQL conn;
		MYSQL *connection = NULL;
		int query_state;

		char query[255];
		
		int running_state = false;
		SignUpSocketServer *signupSocket_p;

	public :
		// Constructor
		
		void init_user(user_info input) {
			strcpy(user.id, input.id);
			strcpy(user.pwd, input.pwd);
		}
		
		void connect_db(void) {
			mysql_init(&conn);
	
			connection = mysql_real_connect(&conn, HOST, USERNAME, PASSWORD, DBNAME, PORTNUM, NULL, 0);

			if (connection == NULL) {
				cout << "DB Not Connected : " << mysql_error(&conn) << endl;
				return;
			}
		}

		
		// 회원 가입 후 아이디와 닉네임은 user.nickname, user.id로 사용하면 될듯!
		void signup(void) {
			cout << "Sign Up"" << endl;

			init_user();	//받아온 정보 저장하는 함수 parameter 추가해야함 

			connect_db();	
		

			sprintf(query, "SELECT * FROM login WHERE id='%s' AND pwd='%s'", user.id, user.pwd);

			query_state = mysql_query(connection, query);

			if (query_state != 0) {
				cout << "Login failed : " << mysql_error(&conn) << endl;
				mysql_close(&conn);
				return;
			}

			sql_result = mysql_store_result(connection);

			while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
				strcpy(user.nickname, sql_row[0]);
				strcpy(user.id, sql_row[1]);
				strcpy(user.pwd, sql_row[2]);
			}	

			mysql_free_result(sql_result);
			mysql_close(&conn);
		}
}

#endif // __MATCHING_H__
