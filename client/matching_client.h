#ifndef __MATCHING_H__
#define __MATCHING_H__

#include "socket_client.h"
#include "../structs/struct.h"
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
			cout << "sendData() run. "<<endl <<endl;
			
			cout << "souce.nickname : " << source.nickname <<"   " <<endl;
			char nickname_c[31];
			strcpy(nickname_c, (source.nickname));
			
			cout << nickname_c << endl;
			
			//send_success = send(sock, (char*) &source.nickname, sizeof(source.nickname), 0);
			
			send_success = send(sock, (char*) &nickname_c, sizeof(nickname_c), 0);
			
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
				return match_success;
			}

			else{
				cout << "Success : receiveData()" <<endl;
				return match_success;
			}

			return match_success;
		}
};

class matching{
	private:
		// data needed for the matching.
		source_of_matching source;

		// data that gotten from the matching.
		result_of_matching result;

		int running_state = false;
		MatchingSocketClient * matchingSock_p;
	public:
		//Constructor
		matching(string nickname){

			running_state = true;
			
			// initalize sources needed for the matching.
			init_source(nickname);
		}


		/* start matching */
		bool runMatching(void){
			cout<<"runMatching"<<endl;	
			
			// connect to the main server through matching socket.
			matchingSock_p = 
				new MatchingSocketClient("matching socket", "13.209.7.127", 9000);
			
			cout<<"runMatching2"<<endl;	

			// send data needed for the matching.
			matchingSock_p->sendData(source);


			cout<<"runMatching3"<<endl;	
				
			bool match_success;

			match_success = matchingSock_p->receiveWaitData();
			while(!match_success){
				cout <<"---Wait---" <<endl;
				matchingSock_p->sendData(source);
				match_success = matchingSock_p->receiveWaitData();
			}
			/*
			 * 매칭이 몇초동안 안되면 강제 연결 종료 시키는 것 여기 추가하면 됨.
			 */
			// get data for the matching from main server.
			result = matchingSock_p->receiveMatchingData();

			if((matchingSock_p->receive_success) == -1)
				displayMatchingFailInfo();

			else
				displayMatchedUserInfo();
			
			delete matchingSock_p;

		}

		void init_source(string nickname){
			source.nickname = nickname;
		}
		

		void displayMatchedUserInfo(){
			cout << "data1 : " << "  "<< endl;
		}

		void displayMatchingFailInfo(){
			cout << "fail matching ( due to server communication failure etc..) "<< endl;
		}
};

class UtilMatching{
	public :
		static void pressMatching(void){
			cout << " press matching button " << endl;
			cout << " ---running matching--- " << endl;
			static matching * matching_object = new matching("hide on bush"); ///// 띄어스기 있는 닉네임 써보기.
			matching_object->runMatching();

			delete matching_object;
		}

		static void endMatching(void){
			cout << " end matching " << endl;
			
		}
};






#endif // __MATCHING_H__
