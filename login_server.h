
#ifndef __LOGIN_SERVER_H__
#define __LOGIN_SERVER_H__

#include "socket_server.h"

using namespace std;
/*
typedef struct LoginQueue{
	int clnt_cnt = 0;
	map< string, int > clnt_id_socket_map;
	map< int, string > clnt_socket_pwd_map;

}login_queue;
*/

typedef struct LoginSocketInfo{
	int clnt_socket;
	string id;
	string pwd;
}login_socket_info;

typedef struct LoginInfo{
	string id;
	string pwd;
}login_info;

class LoginSocketServer : public SocketServer{
	
	/* google style */
	public :
		int clnt_socks[1000];
		int clnt_cnt = 0;
		pthread_mutex_t mutx;

	public :
		/* IF TO DO : server_ip[] 에서 오류나면 스트링으로 바꾸고 스트링으로 서버 주소
		 *  받아서 나중에 사용할때 char *로 변환 해줄 것. */
		LoginSocketServer(string socket_name, int open_port, int clnt_listen_cnt)
			: SocketServer(socket_name, open_port, clnt_listen_cnt){

			this -> prepareServerSocket();
			mutexInit();
			cout << "prepare login "<<endl;
		}
		
		void handleLogin(void){
			pthread_t t_id;
			int clnt_sock_temp;
			while(1){
				acceptClient();
				cout << "accept()" << endl;
				cout << "connect" <<endl;	
				
				pthread_mutex_lock(&mutx);
				clnt_sock_temp = clnt_sock;

				pthread_create(&t_id, NULL, loginClnt, (void*)&clnt_sock_temp);
				pthread_mutex_unlock(&mutx);
				pthread_detach(t_id);
				cout << "Connected client" << endl;	
				
			}

			close(serv_sock);


		}

		void * loginClnt(void * arg){
			int clnt_sock = *((int*)arg);

			
			
			while(1){
				char id_c[31];
				char pwd_c[31];

				if(read(clnt_sock, id_c, sizeof(id_c)) == -1){
					cout << "Error : server -- read() in loginClnt() thread." <<endl;
					close(clnt_sock);
				}
			
					
				if(read(clnt_sock, pwd_c, sizeof(pwd_c)) == -1){
					cout << "Error : server -- read() in loginClnt() thread." <<endl;
					close(clnt_sock);
				}

				string id_s(id_c);
				string pwd_s(pwd_c);

				bool loginSuccess = verifyLogin(id_s, pwd_s);
			
				if(loginSuccess){
					write(clnt_sock, &loginSuccess, sizeof(loginSuccess));
					close(clnt_sock);
					break;
				}
				
				else{	
					write(clnt_sock, &loginSuccess, sizeof(loginSuccess));
				}
			}

			return NULL;
		}


		void mutexInit(void){
			pthread_mutex_init(&mutx, NULL);
		}

		bool verifyLogin(string id, string pwd){
			//디비로부터 아이디 비번 정보를 가져와 있는지 확인 후 있으면 true 반환. 없으면 false반환.
			return true; // 임시.
		}
		
};




#endif // __LOGIN_SERVER_H__
