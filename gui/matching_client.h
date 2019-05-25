#ifndef MATCHING_CLIENT_H
#define MATCHING_CLIENT_H

#include "socket_client.h"

using namespace std;

typedef struct SourceForMatching{
    string nickname;
}source_of_matching;


// To do : data를 string으로 했을 때 다루는 것 해보기.
typedef struct ResultOfMatching{
    int data1;
    int data2;
    int data3;
}result_of_matching;


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

        /*
        int getSocket(){
            return sock;
        }
        */

        /* send data needed for a matching to server.
           return : if sending is succeeded, true. else, false */
        void sendData(source_of_matching source){
            cout << "sendData() run. "<<endl <<endl;

            cout << "souce.data1 : " << source.nickname << "   " <<endl;

            send_success = send(sock, (char *)&source, sizeof(source), 0);

            if(send_success == -1){
                cout<< "Fail : sendData()" <<endl;
            }

            else{
                cout << "Success : sendData()" <<endl;
            }
        }

        /* receive result data for matching
         * If the matching is succeeded, return a string,
         * that is an information of user matched
         * else, return NULL */
        result_of_matching receiveData(void){

            result_of_matching result;
            receive_success = recv(sock, (char *)&result, sizeof(result), 0);

            if(receive_success == -1){
                cout<< "Fail : receiveData()" <<endl;
                return result;
            }

            else{
                cout << "Success : receiveData()" <<endl;
                return result;
            }

        }
};

#endif // MATCHING_CLIENT_H
