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
	bool success;
	int data1;
	int data2;
}result_of_matching;


class MatchingSocketClient : public SocketClient{
	
	/* google style */
	public :
		

	public :
		/* IF TO DO : server_ip[] 에서 오류나면 스트링으로 바꾸고 스트링으로 서버 주소
		 *  받아서 나중에 사용할때 char *로 변환 해줄 것. */
		MatchingSocketClient(string socket_name, char server_ip[], int server_port)
			: SocketClient(socket_name, server_ip, server_port){

			this -> createSocket();
			this -> connectServer();
			
		}
	
		/* receive result data for matching
		 * If the matching is succeeded, return a string, 
		 * that is an information of user matched
		 * else, return NULL */
		result_of_matching receiveData(void){
			int success;

			result_of_matching result;
			success = read(sock, &result, sizeof(result));

			if(!success){
				cout<< "--- read waiting---" <<endl;
			}

			else{
				cout << "Success : succeeded to execute read()" <<endl;
				return result;
			}
		}
		

		void sendData(source_of_matching source){
			int success;

			success = write(sock, &source, sizeof(source));
			
			if(!success){
				cout<< "Fail : fail to send data" <<endl;
			}

			else{
				cout << "Success : succeeded to execute write()" <<endl;
			}
		}
		
		
};


class UtilMatching{
	public :
		static void pressMatching(void){
			cout << " press matching button " << endl;
			cout << " ---running matching--- " << endl;
//			matching.runMatching();
		}

		static void endMatching(void){
			cout << " end matching " << endl;
			
		}
};




class matching{
	private:
		// data needed for the matching.
		static source_of_matching source;

		// data that gotten from the matching.
		static result_of_matching result;

		int running_state = false;

	public:
		//Constructor
		matching(int input_data1, int input_data2, int input_data3){

			running_state = true;
			
			// initalize sources needed for the matching.
			init_source(input_data1, input_data2, input_data3);
		}


		/* start matching */
		static bool runMatching(void){
			
			// connect to the main server through matching socket.
			static MatchingSocketClient * matchingSock_p = 
				new MatchingSocketClient("matching socket", "13.209.15.157", 8888);
			
			// send data needed for the matching.
			matchingSock_p->sendData(source);
			
			// get data for the matching from main server.
			result = matchingSock_p->receiveData();
			
			exitMatching();
		}


		/* send data needed for a matching to server.
		   return : if sending is succeeded, true. else, false */
		bool sendMatchingSources(void){
			int data1;
			int data2;
			int data3;

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
		static void exitMatching(){
			cout << "--- end of matching ---" << endl;
			
			if (result.success)
				displayMatchedUserInfo();

			else
				displayMatchingFailInfo();
		}

		static void displayMatchedUserInfo(){
			cout << "success : " << result.success << "  "
				<< " data :  " << result.data1 << "  " << result.data2 << "  " << endl;
		}

		static void displayMatchingFailInfo(){
			cout << "fail matching ( due to time-out, server communication failure etc..) "<< endl;
		}
};


#endif // __MATCHING_H__
