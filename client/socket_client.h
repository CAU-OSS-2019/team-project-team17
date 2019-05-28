#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <iostream>
#include <string>
//#include <unistd.h>
//#include <arpa/inet.h>
//#include <sys/socket.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#include <string.h>
#include <string>
#include <stdlib.h>
#include "../structs/struct.h"

using namespace std;

// a client socket class for a socket communication.
class SocketClient{

	protected:
		string socket_name;
		char * target_server_ip;
		int target_server_port;

		SOCKET sock;

		struct sockaddr_in serv_addr;

	protected:
		/* create client socket */
		void createSocket(void){
			WSADATA data;
			WORD ver = MAKEWORD(2, 2);
			int wsInit = WSAStartup(ver, &data);

			sock = socket(PF_INET, SOCK_STREAM, 0);

			if(sock == -1)
				cout<< "socket() error" << endl;;

			memset(&serv_addr, 0, sizeof(serv_addr));
			serv_addr.sin_family = AF_INET;
			serv_addr.sin_addr.s_addr = inet_addr(target_server_ip);
			serv_addr.sin_port = htons(target_server_port);
		}

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
		SocketClient(string socket_name, char server_ip[], int server_port)
			: socket_name(socket_name), target_server_ip(server_ip),
			target_server_port(server_port){}


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
