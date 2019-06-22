#ifndef MATCHING_CLIENT_H
#define MATCHING_CLIENT_H

#include "socket_client.h"

using namespace std;

class MatchingSocketClient : public SocketClient{

    /* google style */
    public :
        int receive_success;
        int send_success;

    public :
        /* IF TO DO : server_ip[] 에서 오류나면 스트링으로 바꾸고 스트링으로 서버 주소
         *  받아서 나중에 사용할때 char *로 변환 해줄 것. */
        MatchingSocketClient(string socket_name, char server_ip[], int server_port)
            : SocketClient(socket_name, server_ip, server_port){

            this -> createSocket();
            this -> connectServer();

        }

        ~MatchingSocketClient(){
                    closesocket(sock);
        }
        /*
        int getSocket(){
            return sock;
        }
        */

        /* send data needed for a matching to server.
           return : if sending is succeeded, true. else, false */
        void sendData(source_of_matching source){
            //send_success = send(sock, (char*) &source.nickname, sizeof(source.nickname), 0);

            send_success = send(sock, (char*)&source, sizeof(source_of_matching), 0);
        }

        /* receive result data for matching
         * If the matching is succeeded, return a string,
         * that is an information of user matched
         * else, return NULL */
        result_of_matching receiveMatchingData(void){

            result_of_matching result;

            receive_success = recv(sock, (char*)&result, sizeof(result), 0);

            if(receive_success == -1){
                cout<< "Fail : receiveData()" <<endl;
                return result;
            }

            else{
                cout << "Success : receiveData()" <<endl;
                return result;
            }

        }

        bool receiveWaitData(void){
            bool match_success;
            receive_success = recv(sock, (char*)&match_success, sizeof(match_success), 0);

            if(receive_success == -1){
                cout<< "------Fail : receiveData()---------" <<endl;
                return false;
            }

            else{
                cout << "Success : receiveData()" <<endl;
                return match_success;
            }
        }

        matched_user receiveMatchedUser(void) {
            matched_user user;
            receive_success = recv(sock, (char*)&user, sizeof(matched_user), 0);

            if(receive_success == -1){
                cout<< "Fail : receiveData()" <<endl;
                return user;
            }

            else{
                cout << "Success : receiveData()" <<endl;
                return user;
            }
        }
};

#endif // MATCHING_CLIENT_H
