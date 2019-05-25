#ifndef LOGIN_H
#define LOGIN_H

#include "socket_client.h"

typedef struct LoginInfo{
    string id;
    string pwd;
}login_info;

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

        void sendData(login_info loginInfo) {
            send_success = send(sock, (char*)&loginInfo, sizeof(loginInfo), 0);
            if(send_success == -1){
                cout << "Fail : sendData() in login." << endl;
            }
            else{
                cout << "Success : sendData() in login." << endl;
            }
        }

        void sendbuf(char *buf) {
            send(sock, buf, 1024, 0);
        }

        void recvbuf(char *buf) {
            recv(sock, buf, 1024, 0);
        }

        bool receiveData(void){
            bool loginSuccess;
            receive_success = recv(sock, (char*)&loginSuccess, sizeof(loginSuccess), 0);

            if(receive_success == -1){
                cout << "Fail : receiveData() in login."<< endl;
                return false;
            }

            else{
                cout << "Success : receiveData() in login." << endl;
                loginSuccess = true;
                return loginSuccess;
            }
        }
};

#endif // LOGIN_H
