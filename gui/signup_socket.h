#ifndef SIGNUP_SOCKET_H
#define SIGNUP_SOCKET_H

#include "socket_client.h"

typedef struct signupInfo{
    string id;
    string pwd;
    string nickname;
    string position1;
    string position2;
}signup_info;

class SignupSocketClient : public SocketClient{
    public :
        int receive_success;
        int send_success;
    public :
        SignupSocketClient(string socket_name, char server_ip[], int server_port)
            : SocketClient(socket_name, server_ip, server_port){
            this -> createSocket();
            this -> connectServer();
        }

        void sendData(signup_info signupInfo){
            cout << "client -- sendData() in signup." << endl <<endl;

            cout << "ID : " << signupInfo.id << endl;
            cout << "PWD : " << signupInfo.pwd << endl;

            send_success = send(sock, (char*)&signupInfo, sizeof(signupInfo), 0);

            if(send_success == -1){
                cout << "Fail : sendData() in signup." << endl;
            }

            else{
                cout << "Success : sendData() in signup." << endl;
            }
        }

        bool receiveData(void){
            bool signupSuccess;
            receive_success = recv(sock, (char*)&signupSuccess, sizeof(signupSuccess), 0);

            if(receive_success == -1){
                cout << "Fail : receiveData() in signup." << endl;
                return false;
            }

            else{
                cout << "Success : receiveData() in signup." << endl;
                return signupSuccess;
            }
        }
};

#endif // SIGNUP_SOCKET_H
