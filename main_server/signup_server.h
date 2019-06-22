
#ifndef __LOGIN_SERVER_H__
#define __LOGIN_SERVER_H__

#include "db/signup_server_db.h"
#include "../structs/struct.h"
using namespace std;
/*
typedef struct LoginQueue{
	int clnt_cnt = 0;
	map< string, int > clnt_id_socket_map;
	map< int, string > clnt_socket_pwd_map;

}login_queue;
*/


/*

typedef struct UserInfo {
	
	string nickname;
	string id;
	string pwd;
	
}user_info;

*/

class SignupSocketServer : public SocketServer{
	
	/* google style */
	public :
		int clnt_socks[1000];
		int clnt_cnt = 0;
		pthread_mutex_t mutx;

	public :
		/* IF TO DO : server_ip[] 에서 오류나면 스트링으로 바꾸고 스트링으로 서버 주소
		 *  받아서 나중에 사용할때 char *로 변환 해줄 것. */
		SignupSocketServer(string socket_name, int open_port, int clnt_listen_cnt)
			: SocketServer(socket_name, open_port, clnt_listen_cnt){

			this -> prepareServerSocket();
			
			cout << "prepare signup "<<endl;

			pthread_mutex_init(&mutx,NULL);
		}/*
		static void* handleLogin_helper(void *context){
			return ((LoginSocketServer*)context)->handleLogin();
		}*/	
		void* handleSignup(){
			pthread_t t_id;
			int clnt_sock_temp;
			while(1){
				acceptClient();
				cout << "accept()" << endl;
				cout << "connect" <<endl;	
				
				pthread_mutex_lock(&mutx);
				clnt_sock_temp = clnt_sock;

				pthread_create(&t_id, NULL, signupClnt, (void*)&clnt_sock_temp);
				pthread_mutex_unlock(&mutx);
				pthread_detach(t_id);
				cout << "Connected client" << endl;	
				
			}

			close(serv_sock);
			return NULL;

		}

		static void * signupClnt(void * arg){
			int clnt_sock = *((int*)arg);
			
			
			//while(1){

				/*
				char id_c[31];
				char pwd_c[31];
				*/

				signup_info * signup_info_p;
				char buffer[sizeof(signup_info)];
				if(read(clnt_sock, buffer, sizeof(buffer)) == -1){//클라이언트로부터 로그인 데이터를 받을때까지 대기, 제대로 받았는지 체크
					cout << "Error : server -- read() in signupClnt() thread." <<endl;
					close(clnt_sock);
				}

				cout <<"sizeof : "<<sizeof(character_info) <<endl;

				cout << "BUFFER SIZE :" <<sizeof(buffer)<<endl;
			
				/*
				if(read(clnt_sock, pwd_c, sizeof(pwd_c)) == -1){
					cout << "Error : server -- read() in loginClnt() thread." <<endl;
					close(clnt_sock);
				}
				

				string id_s(id_c);
				string pwd_s(pwd_c);
				*/
				signup_info_p = (signup_info*)buffer;
				SignUp signup_temp;
				
				/* for debugging */
				cout << "id : " << signup_info_p->id
					<< "pwd : " << signup_info_p->pwd
				<< "nickname : " << signup_info_p->nickname << endl;
					
				bool signupSuccess = signup_temp.signup((*signup_info_p));
			
				if(signupSuccess){
					write(clnt_sock, &signupSuccess, sizeof(signupSuccess));
					//break;
				}
				
				else{	
					write(clnt_sock, &signupSuccess, sizeof(signupSuccess));
					//break;
				}
			//}
			close(clnt_sock);
			return NULL;
		}


		void mutexInit(void){
			pthread_mutex_init(&mutx, NULL);
		}

		static bool verifyLogin(string id, string pwd){
			int a = 1;
			//디비로부터 아이디 비번 정보를 가져와 있는지 확인 후 있으면 true 반환. 없으면 false반환.
			return true; // 임시.
		}
		
};




#endif // __LOGIN_SERVER_H__
