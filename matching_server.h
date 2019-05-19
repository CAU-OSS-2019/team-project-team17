#ifndef __MATCHING_H__
#define __MATCHING_H__

#include "socket_server.h"
#include <set>

using namespace std;

typedef struct SourceOfMatching{
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

typedef struct MatchingQueue{
	int clnt_cnt = 0;
	set<int> clnt_sockets;
	set<char *> nicknames;
}matching_queue;

class MatchingSocketServer : public SocketServer{
	
	/* google style */
	public :
		int receive_success;
		int send_success;
		matching_queue matchingQueue;
		pthread_t t_id;
		pthread_mutex_t matching_mutex;
		pthread_mutex_t matching_queue_mutex;

	public :
		/* IF TO DO : server_ip[] 에서 오류나면 스트링으로 바꾸고 스트링으로 서버 주소
		 *  받아서 나중에 사용할때 char *로 변환 해줄 것. */
		MatchingSocketServer(string socket_name, int open_port, int clnt_listen_cnt)
			: SocketServer(socket_name, open_port, clnt_listen_cnt){

			this -> prepareServerSocket();
		}
		
		void handleMatching(void){
			int thread_create_success = -1;
			mutexInit();

			pthread_mutex_lock(&matching_mutex);
			while(1){
				acceptClient();
				
				pthread_mutex_lock(&matching_queue_mutex);
				
				matchingQueue.clnt_sockets.insert(clnt_sock);

				//matchingQueue.clnt_sockets.insert(make_pair(matchingQueue.clnt_cnt, clnt_sock));
				// (matchingQueue.clnt_sockets)[matchingQueue.clnt_cnt] = clnt_sock;
				char * buffer = (char *)malloc(sizeof(char)*31);
				
				// sizeof(buffer) 크기 측정해보기. 4byte로 나오면 안됨.
				if(read(clnt_sock, buffer, sizeof(buffer)) == -1)
					cout << "Error : server -- read() in handleMatching()."<<endl;
				matchingQueue.nicknames.insert(buffer);

				//matchingQueue.nicknames.insert(make_pair(matchingQueue.clnt_cnt, buffer));

				matchingQueue.clnt_cnt++;
				
				if(matchingQueue.clnt_cnt == 10){
					Matching matching(matchingQueue);
					matched_user matchedUser = matching.runMatching();
					sendData(matchedUser);
					removeMatchedUserFromQueue(matchedUser);
				}
				pthread_mutex_unlock(&matching_queue_mutex);
				
				
			}
			pthread_mutex_unlock(&matching_mutex);


		}

		void sendData(matched_user matchedUser){
			cout << "server --- sendData() run. "<<endl;

			write(

		}

		void mutexInit(void){
			pthread_mutex_init(&matching_mutex);
			pthread_mutex_init(&matching_queue_mutex, NULL);
		}

		void removeMatchedUserFromQueue(matched_user matchedUser){
			// nickname에 해당하는 것 있는 키 값 얻어서 그 부분 없앰. sockets에서도 그 인덱스 부분 없앰. 
		}

};

struct matchedUser{
	string userNickname1;
	string userNickname2;
}matched_user;

class Matching{
	private:
		// data needed for the matching.
		source_of_matching source;

		// data that gotten from the matching.
		result_of_matching result;
		
		matching_queue matchingQueue;

		int running_state = false;
		MatchingSocketServer * matchingSock_p;
	public:
		//Constructor
		Matching(matching_queue matchingQueueInput)
			: matchingQueue(matchingQueueInput){}
		
		/* start matching */
		matched_user runMatching(void){
			cout<<"runMatching"<<endl;
			// runAlgorithm(matchingQueue.nicknames);
		}
		
		double runAlgorithm(string userNickname1, string userNickname2){
			// 디비에서 각 유저들 정보 꺼내와서
			// 알고리즘 돌리고
			// 그 결과(double 적합도)를 반환.
		}
		
		/*
		 source_of_matching getSourceFromDB(string userNickname){
		 	//디비에서 그 유저의 정보 꺼내오기.
		 }
		 */






















			// connect to the main server through matching socket.
			matchingSock_p = 
				new MatchingSocketClient("matching socket", "13.209.15.157", 8888);
			
			cout<<"runMatching2"<<endl;	

			// send data needed for the matching.
			matchingSock_p->sendData(source);


			cout<<"runMatching3"<<endl;	

			// get data for the matching from main server.
			result = matchingSock_p->receiveData();
			
			cout<<"runMatching4"<<endl;	

			exitMatching(matchingSock_p->receive_success);
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
		void exitMatching(int receive_success){
			cout << "--- end of matching ---" << endl;
			
			if (receive_success)
				displayMatchedUserInfo();

			else
				displayMatchingFailInfo();
		}

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
