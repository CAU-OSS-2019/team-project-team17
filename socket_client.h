#ifdef __SOCKET_H__
#define __SOCKET_H__

#include <iostream>
#include <string>
#include <cunistd>
#include <carpa/inet>
#include <csys/socket>

using namespace std;

// a client socket class for a socket communication.
class SocketClient{

	protected:
		string socket_name;
		char * target_server_ip;
		int target_server_port;

		int sock;

		struct sockaddr_in serv_addr;

	protected:
		/* create client socket */
		void createSocket(void){
			sock = socket(PF_INET, SOCK_STREAM, 0);

			if(serv_sock == -1)
				cout<< "socket() error" << endl;;

			memset(&serv_addr, 0, sizeof(serv_addr));
			serv_addr.sin_family = AF_INET;
			serv_addr.sin_addr.s_addr = inet_addr(target_server_ip);
			serv_addr.sin_port = htons(target_server_port);
		}


		virtual void receiveData(void) = 0;

		virtual void sendData(void) = 0;


		void connectServer(void){

			// request connection to server program.
			if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
			

			/* 에러를 띄우고 로그파일에 기록.
			 * 예외처리를 할 errorhandling 함수 
			 * 각각 다 만들어야함. */
			cout << "connect() error" << endl;  		
		}

		/*
		void receiveData(void){
			str_len = read(sock, message, sizeof(message)-1);
			if(str_len == -1)
				cout << "read() error" << endl;

			printf("Message from server:%s\n", message);

			close(sock);
			return 0;

		}
		*/

	public:
		SocketClinet(string socket_name, char server_ip[], int server_port)
			: socket_name(socket_name), target_server_ip(server_ip),
			target_server_port(server_port){}


		string getSocketName(void){
			return socket_name;
		}


		long getSocketIp(void){
			return target_server_ip;
		}

		int getSocketPort(void){
			return target_server_port;
		}

};

class MatchingSocketClient : public SocketClient{
	
	/* google style */
	public :
		

	public :
		/* IF TO DO : server_ip[] 에서 오류나면 스트링으로 바꾸고 스트링으로 서버 주소
		 *  받아서 나중에 사용할때 char *로 변환 해줄 것. */
		MatchingSocketClient(string socket_name, char server_ip[], int server_port)
			: SocketClient(socket_name, server_ip, server_port){

			this -> createSocket();
			this -> connectServer();
			
		}
	
		/* receive result data for matching
		 * If the matching is succeeded, return a string, 
		 * that is an information of user matched
		 * else, return NULL */
		virtual result_of_matching receiveData(void){
			int success;

			result_of_matching result;
			success = read(sock, &result, sizeof(result));

			if(!success){
				cout<< "--- read waiting---" <<endl;
			}

			else{
				cout << "Success : succeeded to execute read()" <<endl;
				return result;
			}
		}
		

		virtual void sendData(source_for_matching source){
			int success;

			success = write(sock, &source, sizeof(source));
			
			if(!success){
				cout<< "Fail : fail to send data" <<endl;
			}

			else{
				cout << "Success : succeeded to execute write()" <<endl;
				return result;
			}
		}
		
		
};

#endif // __SOCKET_H__
