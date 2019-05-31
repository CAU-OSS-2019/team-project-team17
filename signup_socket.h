#ifndef SIGNUP_SOCKET_H
#define SIGNUP_SOCKET_H

#include "socket_client.h"

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
            send_success = send(sock, (char*)&signupInfo, sizeof(signupInfo), 0);
        }

        bool receiveData(void){
            bool signupSuccess;
            receive_success = recv(sock, (char*)&signupSuccess, sizeof(signupSuccess), 0);

            if(receive_success == -1){
                return false;
            }
            else{
                return signupSuccess;
            }
        }
};

#endif // SIGNUP_SOCKET_H
