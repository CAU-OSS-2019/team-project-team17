
// a Socket class for a socket communication.
class Socket{

	private:
		string socket_name;
		long target_server_ip;
		int target_server_port;
		int serv_sock;
		int clnt_sock;

		struct sockaddr_in serv_addr;
		struct sockaddr_in clnt_addr;

		socklen_t clnt_addr_size;

		char message[] = "Hello World!";



	public:
		SocketCommunication(string socket_name, long server_ip, int server_port)
			: socket_name(socket_name), server_ip(target_server_ip),
			target_server_port(target_server_port){}	

		/* In case of a server socket, 
		 * there must be socket array or etc ds of sockets
		 * as local variable in a function createSokcet. */
		void createSocket(void){
			serv_sock = socket(PF_INET, SOCK_STREAM, 0);

			if(serv_sock == -1)
				error_handling("socket() error");

			memset(&serv_addr, 0, sizeof(serv_addr));
			serv_addr.sin_family = AF_INET;
			serv_addr.sin_addr.s_addr = htonl(target_server_ip);
			serv_addr.sin_port = htons(target_server_port);
		}


		void sendData(void){
			if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
				cout << "bind() error" << endl;  // 에러를 띄우고 로그파일에 기록.
			if(listen(serv_sock,5) == -1)
				cout << "listen() error" << endl;

		}


		string getSocketName(void){
			return socket_name;
		}


		long getSocketIp(void){
			return target_server_ip;
		}

		int getSocketPort(void){
			return target_server_port;
		}

}
