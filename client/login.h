#ifndef __LOGIN_H__
#define __LOGIN_H__

#include "socket_client.h"
#include "../structs/struct.h"


class LoginSocketClient : public SocketClient{
	public :
		int receive_success;
		int send_success;
	public :
		LoginSocketClient(string socket_name, char server_ip[], int server_port)
			: SocketClient(socket_name, server_ip, server_port){
			this -> createSocket();
			this -> connectServer();
		}

		void sendData(login_info loginInfo){
			cout << "client -- sendData() in login."<< endl <<endl;
			
			cout << "ID : " << loginInfo.id << endl;
			cout << "PWD : " << loginInfo.pwd << endl;

			send_success = send(sock, (char*)&loginInfo, sizeof(loginInfo), 0);

			if(send_success == -1){
				cout << "Fail : sendData() in login." << endl;
			}

			else{
				cout << "Success : sendData() in login." << endl;
			}
			
			
		}

		bool receiveData(void){
			bool loginSuccess;
			receive_success = recv(sock, (bool*)&loginSuccess, sizeof(loginSuccess), 0);
			
			if(receive_success == -1){
				cout << "Fail : receiveData() in login."<< endl;
				return false;
			}
			
			else{
				cout << "Success : receiveData() in login." << endl;
				return loginSuccess;
			}
		}
};

class Login{
	private :
		login_info loginInfo;
		login_info inputLoginInfo;

		LoginSocketClient * loginSock_p;
		bool loginSuccess = false;
	
	public :
		Login(void){

		}
		
		void runLogin(void){
			validateCheckLogin();
		}
			
		void validateCheckLogin(void){
			cout << "client -- validateCheckLogin()" <<endl;
			
			while(!loginSuccess){
				enterLoginInfo();
				
				loginSock_p =
					new LoginSocketClient("login socket", "13.209.7.127", 9100);

				loginSock_p -> sendData(inputLoginInfo);
				loginSuccess = loginSock_p -> receiveData();
				delete loginSock_p;
			}

			displayAppMainWindow();
			loginSuccess = false;
		}
		
		void enterLoginInfo(void){
			cout << "enter ID : ";
			cin >> inputLoginInfo.id;
			
			cout << "enter Pwd : ";
			cin >> inputLoginInfo.pwd;
		}

		void displayAppMainWindow(){

		}
};


#endif
