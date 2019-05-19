#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <iostream>
#include <string>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <string>
#include <pthread.h>
#define MAX_CLNT 1000


using namespace std;

// a client socket class for a socket communication.
class SocketServer{

	protected:
		string socket_name;
		int opened_port;
		int serv_sock;
		int clnt_sock;

		/* 이 서버 소켓 객체에서 연결 요청을 받을 클라이언트의 개수. */
		int clnt_cnt_listen;

		struct sockaddr_in serv_addr;
		struct sockaddr_in clnt_addr;
	
		int clnt_addr_size;

	protected:
		void prepareServerSocket(void){
			createSocket();
			connectClient();
			enterListenState();
		}

		/* create server socket */
		void createSocket(void){
			serv_sock = socket(PF_INET, SOCK_STREAM, 0);

			if(serv_sock == -1)
				cout<< "server -- socket() error" << endl;;

			memset(&serv_addr, 0, sizeof(serv_addr));
			serv_addr.sin_family = AF_INET;
			serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
			serv_addr.sin_port = htons(opened_port);
		}

		void connectClient(void){
			if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
				cout << "Error : server -- bind()" << endl;

		}

		void enterListenState(void){
			if(listen(serv_sock, clnt_cnt_listen) == -1)
				cout << "Error : server -- listen()" << endl;
		}

		void acceptClient(void){
			clnt_addr_size = sizeof(clnt_addr);
			clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);

			if(clnt_sock == -1)
				cout << "Error : server -- accept()" << endl;
			
			else
				cout << "Connected client IP : " << inet_ntoa(clnt_addr.sin_addr)
					<<endl;
		}
		
	public:
		SocketServer(string socket_name, int open_port, int clnt_listen_cnt)
			: socket_name(socket_name), opened_port(open_port), 
				clnt_cnt_listen(clnt_listen_cnt){}


		string getSocketName(void){
			return socket_name;
		}


		char* getSocketIp(void){
			return target_server_ip;
		}

		int getSocketPort(void){
			return target_server_port;
		}

};


#endif // __SOCKET_H__
