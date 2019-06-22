#ifndef __SIGNUP_H__
#define __SIGNUP_H__

#include "socket_server.h"
#include "../../structs/struct.h"
#include "../signup_server.h"
#include </usr/include/mysql/mysql.h>

#define HOST "gamehaeduo-db.c8xdbny5rkis.ap-northeast-2.rds.amazonaws.com"
#define USERNAME "gamehaeduo"
#define PASSWORD "caugamehaeduo"
#define DBNAME "gamehaeduo"
#define PORTNUM 3306

using namespace std;


/*
class SignUpSocketServer : public SocketServer {
	public :
		int receive_success;
		int send_success;
		pthread_mutex_t signup_mutex;
	
	public :
		SignupSocketServer(string socket_name, char server_ip[], int server_port)
			: SocketClient(socket_name, server_ip, server_port){

			this -> prepareServerSocket();
			
		}
		
		void handleSignUp(void) {
			int tread_create_success = -1;
			pthread_init(&signup_mutex, NULL);

			pthread_mutex_lock(&signup_mutex);
			
		}            
		
}
*/

class SignUp {
	private :

		// variables for signup
		MYSQL conn;
		MYSQL *connection = NULL;
		int query_state;
		char query[255];

		// variables for socket
		int running_state = false;
	//	SignupSocketServer *signupSocket_p;

	public :
		// Constructor
		
		
		// 회원 가입 후 아이디와 닉네임은 user.nickname, user.id로 사용하면 될듯!
		bool signup(signup_info input) {
			cout << "Sign Up" << endl;

			// Connect
			mysql_init(&conn);

			connection = mysql_real_connect(&conn, HOST, USERNAME, PASSWORD, DBNAME, PORTNUM, NULL, 0);

			if (connection == NULL) {
				cout << "DB Not Connected : " << mysql_error(&conn) << endl;
				return false;
			}	
			
			mysql_set_character_set(&conn,"utf8");

			// Query
			sprintf(query, "INSERT INTO login VALUES ('%s', '%s', '%s')", input.nickname, input.id, input.pwd);

			query_state = mysql_query(connection, query);
	
			if (query_state != 0) {
				cout << "Sign Up failed" << mysql_error(&conn) << endl;
				mysql_close(&conn);
				return false;
			}

			// Close
			mysql_close(&conn);

			return true;
		}
};

#endif // __SIGNUP_H__
