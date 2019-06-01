#ifndef LOGIN_H
#define LOGIN_H

#include "socket_client.h"
#include <QString>
#include <QTextCodec>

class LoginSocketClient : public SocketClient{
    public :
        int receive_success;
        int send_success;
        login_data user;
    public :
        LoginSocketClient(string socket_name, char server_ip[], int server_port)
            : SocketClient(socket_name, server_ip, server_port){
            this -> createSocket();
            this -> connectServer();
        }

        void sendData(login_info loginInfo) {
            cout << loginInfo.id << " " << loginInfo.pwd << endl;
            send_success = send(sock, (char*)&loginInfo, sizeof(login_info), 0);
        }

        void sendbuf(char *buf) {
            send(sock, buf, 1024, 0);
        }

        void recvbuf(char *buf) {
            recv(sock, buf, 1024, 0);
        }

        login_data receiveData(void){
//            char buf[sizeof(login_data)];
            receive_success = recv(sock, (char*)&user, sizeof(login_data), 0);
            /*user = (login_data *)buf;

            char msg[32];
            cout << strcpy(msg, user->nickname) << endl;
            cout << strcpy(msg, user->rank) << endl;
            bool hi = user->loginSuccess;
            cout << hi << endl;
*/
            QString strLine;
            QTextCodec *codec = QTextCodec::codecForLocale();
            QString strUnicodeLine;
            strLine = user.nickname;
            strUnicodeLine = codec->toUnicode( strLine.toLocal8Bit() );
            char buf[32];
            strcpy(buf, strUnicodeLine.toLocal8Bit().constData());
            strcpy(user.nickname, buf);
            cout << "rank: " << user.rank << endl;
            cout << "nick: " << user.nickname << endl;
            cout << "bool: " << user.loginSuccess << endl;
            if(receive_success == -1){
                cout << "Fail : receiveData() in login."<< endl;
                return user;
            }

            else{
                cout << "Success : receiveData() in login." << endl;
                return user;
            }
        }
};

#endif // LOGIN_H
