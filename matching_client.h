#ifndef __MATCHING_H__
#define __MATCHING_H__

#include "socket_client.h"

using namespace std;

typedef struct SourceForMatching{
	int data1;
	int data2;
	int data3;
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
		
		~MatchingSocketClient(){
			close(sock);
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
			
			cout << "souce.data1 : " << source.data1 <<"   " 
				<<"source.data2 : " <<source.data2 <<"   " 
				<< "source.data3 : "<<source.data3 <<"   " <<endl;

			send_success = write(sock, &source, sizeof(source));
			
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
			receive_success = read(sock, &result, sizeof(result));

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
		matching(int input_data1, int input_data2, int input_data3){

			running_state = true;
			
			// initalize sources needed for the matching.
			init_source(input_data1, input_data2, input_data3);
		}


		/* start matching */
		bool runMatching(void){
			cout<<"runMatching"<<endl;	
			
			// connect to the main server through matching socket.
			matchingSock_p = 
				new MatchingSocketClient("matching socket", "13.209.15.157", 8888);
			
			cout<<"runMatching2"<<endl;	

			// send data needed for the matching.
			matchingSock_p->sendData(source);


			cout<<"runMatching3"<<endl;	

			// get data for the matching from main server.
			result = matchingSock_p->receiveData();

			if((matchingSock_p->receive_success) == -1)
				displayMatchingFailInfo();

			else
				displayMatchedUserInfo();
			
			delete matchingSock_p;

		}

		void init_source(int input_data1, int input_data2, int input_data3){
			source.data1 = input_data1;
			source.data2 = input_data2;
			source.data3 = input_data3;
		}
		

		/* To do : 
		 * free all dynamic allocation related to the matching 
		 * or if needed, initialize member variables
		 * and then exit matching.*/
		
		/*
		void exitMatching(int receive_success){

		}
		*/

		void displayMatchedUserInfo(){
			cout << "data1 : " << result.data1 << "  "
				<< " data2 :  " << result.data2 << "  " << "data3 : "<<result.data3 << "  " << endl;
		}

		void displayMatchingFailInfo(){
			cout << "fail matching ( due to time-out, server communication failure etc..) "<< endl;
		}
};

class UtilMatching{
	public :
		static void pressMatching(void){
			cout << " press matching button " << endl;
			cout << " ---running matching--- " << endl;
			static matching * matching_object = new matching(1,2,3);
			matching_object->runMatching();

			delete matching_object;
		}

		static void endMatching(void){
			cout << " end matching " << endl;
			
		}
};






#endif // __MATCHING_H__
