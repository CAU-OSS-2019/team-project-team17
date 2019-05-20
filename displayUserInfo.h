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

typedef UserGameInfo {

	string nickname;
	string rank;
	
}user_game_info;

/*
class DisplayUserInfoSocketServer : public SocketServer {
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

class DisplayUserInfo {
	private :
		// variables for displayUserInfo
		user_game_info user;

		MYSQL conn;
		MYSQL *connection = NULL;
		int query_state;
		char query[255];
		
		// variables for socket
		int running_state = false;
		DisplayUserInfoSocketServer *userInfoSocket_p;

		void connect_db(void) {
			mysql_init(&conn);

			connection = mysql_real_connect(&conn, HOST, USERNAME, PASSWORD, DBNAME, PORTNUM, NULL, 0);

			if (connection == NULL) {
				cout << "DB Not Connected : " << mysql_error(&conn) << endl;
				return;
			}
		}

		void set_user_info(MYSQL_ROW input) {
			user.nickname = input[0];
			user.rank = input[1];


		}

	public :
		// Constructor
		
		
		user_game_info displayUserInfo(string id) {
			cout << "Display User Info" << endl;

			connect_db();	
		

			sprintf(query, "SELECT nickname, rank FROM userEntireInfo NATURAL JOIN login WHERE id='%s' LIMIT 1", id.c_str());

			query_state = mysql_query(connection, query);

			if (query_state != 0) {
				cout << "Display User Info failed : " << mysql_error(&conn) << endl;
				mysql_close(&conn);
				return user;
			}

			sql_result = mysql_store_result(connection);

			while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {

				set_user_info(sql_row);

			}	

			mysql_free_result(sql_result);
			mysql_close(&conn);

			return user;
		}
}

#endif // __DISPLAYUSERINFO_H__
