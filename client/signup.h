#ifndef __SIGN_UP__
#define __SIGN_UP__

#include "socket_client.h"
#include "../structs/struct.h"


class SignupSocketClient : public SocketClient{
	public :
		int receive_success;
		int send_success;
	public :
		LoginSocketClient(string socket_name, char server_ip[], int server_port)
			: SocketClient(socket_name, server_ip, server_port){
			this -> createSocket();
			this -> connectServer();
		}
		
		void sendData(signup_info signupInfo){
			cout << "client -- sendData() in signup." << endl <<endl;
		
			cout << "ID : " << signupInfo.id << endl;
			cout << "PWD : " << loginInfo.pwd << endl;

			send_success = send(sock, (char*)&signupInfo, sizeof(signupInfo), 0);//회원가입 정보 보냄

			if(send_success == -1){
				cout << "Fail : sendData() in signup." << endl;
			}
			
			else{
				cout << "Success : sendData() in signup." << endl;
			}
		}

		bool receiveData(void){
			bool signupSuccess;
			receive_success = recv(sock, (char *)&signupSuccess, sizeof(signupSuccess), 0);

			if(receive_success == -1){
				cout << "Fail : receiveData() in signup." << endl;
				return false;
			}
			
			else{
				cout << "Success : receiveData() in signup." << endl;
				return signupSuccess;
			}
		}
}

class signup{
	private:
		signup_info signupInfo;
		signup_info inputSignupInfo;

		SignupSocketClient * signupSock_p;
		bool signupSuccess = false;
		
	public:
		signup(void){
		
		}
		
		void runSignup(void){
			validateCheckSignup();
		}

		void validateCheckSignup(void){
			cout << "client -- validateCheckSignup()" << endl;

			while(!signupSuccess){			
				enterSignupInfo();
				
				signupSock_p = 
					new SignupSocketClient("signup socket", "13.209.7.127", 9200);
				
				signupSock_p -> sendData(inputSignupInfo);
				signupSuccess = signupSock_p -> receiveData();
				delete signupSock_p;
			
			}

			displayAppLoginWindow();
			signupSuccess = false;
		}		

		
		void enterSignupInfo(void){
			cout << "enter ID : ";
			cin >> inputSignupInfo.id;
			
			cout << "enter Pwd : ";
			cin >> inputSignupInfo.pwd;
			
			cout << "enter Nickname : ";
			cin >> inputSignupInfo.nickname;
				
			cout << "enter your position1 : ";
			cin >> inputSignupInfo.position1;
		
			cout << "enter your position2 : ";
			cin >> inputSignupInfo.position2;
		}
		
		void displayAppMainWindow(){

		}
		
}

#endif // __SIGN_UP__
