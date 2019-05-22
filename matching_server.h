#ifndef __MATCHING_H__
#define __MATCHING_H__

#include "socket_server.h"
#include <map>

#define MATCHING_QUEUE_SIZE 2  // must be >=2

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
	map< string, int > clnt_nickname_socket_map;

}matching_queue;

typedef struct matchedUser{
	string userNickname1;
	//result_of_matching userInfo1;
	int userInfo1;

	string userNickname2;
	//result_of_matching userInfo2;
	int userInfo2;

}matched_user;



class Matching{
	private:
		// data needed for the matching.
		source_of_matching source;

		// data that gotten from the matching.
		result_of_matching result;
		
		matching_queue matchingQueue;

		int running_state = false;

	public:
		//Constructor
		Matching(matching_queue matchingQueueInput)
			: matchingQueue(matchingQueueInput){}
		
		/* start matching */
		matched_user runMatching(void){
			cout<<"runMatching"<<endl;
			/////////////////////////////// userConformity 유저별로 저장해놓고 나중에 매칭 속도 빠르게도 할 수 있을 듯.
			int i = 0;
			string userNickname[MATCHING_QUEUE_SIZE];
			map< string, int >::iterator iter;
			
			for(iter = (matchingQueue.clnt_nickname_socket_map).begin();
				iter != (matchingQueue.clnt_nickname_socket_map).end() && i <MATCHING_QUEUE_SIZE;
					 ++i, ++iter){
				userNickname[i] = iter->second;
			}
			
			return compareConformity(userNickname);
		}
		

		matched_user compareConformity(string userNickname[]){
			double userConformity[MATCHING_QUEUE_SIZE][MATCHING_QUEUE_SIZE-1];
			
			double max = 0;
			int maxI =0, maxJ =0;
			
			userConformity[0][0] = -1;
			max = runAlgorithm(userNickname[0], userNickname[1]);
			for(int i = 0; i < MATCHING_QUEUE_SIZE; i++){
				for(int j = i+1; j < MATCHING_QUEUE_SIZE; j++){
					userConformity[i][j] = runAlgorithm(userNickname[i], userNickname[j]);
					
					if(max < userConformity[i][j]){
						max = userConformity[i][j];
						maxI = i;
						maxJ = j;
					}
				}
			}
			
			// matched_user bestMatchedUser(userNickname[maxI], ,userNickname[maxJ], )
			matched_user bestMatchedUser = {userNickname[maxI], 1, userNickname[maxJ], 2};
			return  bestMatchedUser;
		}
		
		double runAlgorithm(string userNickname1, string userNickname2){
			return 1;
			// 디비에서 각 유저들 정보 꺼내와서
			// 알고리즘 돌리고
			// 그 결과(double 적합도)를 반환.
		}
		
		/*
		 source_of_matching getSourceFromDB(string userNickname){
		 	//디비에서 그 유저의 정보 꺼내오기.
		 }
		 */
};




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
			cout << "test"<<endl;
		}/*
		static void *handleMatching_helper(void *context){
			return ((MatchingSocketServer*)context)->handleMatching();
		}*/
		void * handleMatching(){
			int thread_create_success = -1;
			mutexInit();

			pthread_mutex_lock(&matching_mutex);
			while(1){
				acceptClient();
				cout << "accept()" << endl;
				pthread_mutex_lock(&matching_queue_mutex);
				cout << "connect" <<endl;	
				
				/*
				string buffer_s;
				
				if(read(clnt_sock, &buffer_s, sizeof(buffer_s)) == -1){
					cout << "Error : server -- read() in handleMatching()."<<endl;
					cout << "kyeong tae" <<endl;
					close(clnt_sock);
				}
				*/

				
				char buffer[31];
				
				// sizeof(buffer) 크기 측정해보기. 4byte로 나오면 안됨.
				if(read(clnt_sock, buffer, sizeof(buffer)) == -1){
					cout << "Error : server -- read() in handleMatching()."<<endl;
					close(clnt_sock);
				}

				string buffer_s(buffer);
				
				
				matchingQueue.clnt_nickname_socket_map.insert(make_pair(buffer_s, clnt_sock));

				matchingQueue.clnt_cnt++;
				
				if(matchingQueue.clnt_cnt == MATCHING_QUEUE_SIZE){
					// memory 낭비 없애려면 동적 할당으로 구현해도 될 듯.
					Matching * matching = new Matching(matchingQueue);
					matched_user matchedUser = matching->runMatching();
					delete matching;
					
					sendMatchingData(matchedUser, true);
					removeMatchedUserFromQueue(matchedUser);
					
					bool match_success = false;	
					sendWaitData(match_success);
				}
				
				else{
					bool match_success = false;
					sendWaitData(match_success);
				}

				pthread_mutex_unlock(&matching_queue_mutex);
				
				
			}
			pthread_mutex_unlock(&matching_mutex);

			return NULL;
		}

		void sendMatchingData(matched_user matchedUser, bool match_success){
			cout << "server --- sendMatchingData() run. "<<endl;
			
			//되는지 확인해보기 맵에서 값 접근 방법 -  a[1] 접근
			map< string, int >::iterator matchingUserIter1;
			map< string, int >::iterator matchingUserIter2;
			matchingUserIter1 = matchingQueue.clnt_nickname_socket_map.find(matchedUser.userNickname1);
			matchingUserIter2 = matchingQueue.clnt_nickname_socket_map.find(matchedUser.userNickname2);
			int userSock1 = matchingUserIter1->second;
			int userSock2 = matchingUserIter2->second;
			
			write(userSock1, &match_success, sizeof(match_success));
			write(userSock1, &matchedUser.userInfo1, sizeof(matchedUser.userInfo1));
			
			write(userSock2, &match_success, sizeof(match_success));
			write(userSock2, &matchedUser.userInfo2, sizeof(matchedUser.userInfo2));

		}
		
		void sendWaitData(bool match_success){
			cout << "server --- sendWaitData() run."<<endl;
			
			map< string, int >::iterator allUserIter;

			for(allUserIter = matchingQueue.clnt_nickname_socket_map.begin();
				allUserIter != matchingQueue.clnt_nickname_socket_map.end();
					++allUserIter){

				int userSock = (allUserIter -> second);
				write(userSock, &match_success, sizeof(match_success));

			}

		}

		void mutexInit(void){
			pthread_mutex_init(&matching_mutex, NULL);
			pthread_mutex_init(&matching_queue_mutex, NULL);
		}

		void removeMatchedUserFromQueue(matched_user matchedUser){
			// nickname에 해당하는 것 있는 키 값 얻어서 그 부분 없앰. sockets에서도 그 인덱스 부분 없앰. 
			
			map< string, int >::iterator matchingUserIter1;
			map< string, int >::iterator matchingUserIter2;
			matchingUserIter1 = matchingQueue.clnt_nickname_socket_map.find(matchedUser.userNickname1);
			matchingQueue.clnt_nickname_socket_map.erase(matchingUserIter1);
			--matchingQueue.clnt_cnt;
			
			matchingUserIter2 = matchingQueue.clnt_nickname_socket_map.find(matchedUser.userNickname2);
			matchingQueue.clnt_nickname_socket_map.erase(matchingUserIter2);
			--matchingQueue.clnt_cnt;

			/* 
			
			matchingUserIter1 = matchingQueue.clnt_nickname_socket_map.find(matchedUser.userNickname1);
			matchingQueue.clnt_nickname_socket_map.erase(matchedUser.userNickname1);
			
			matchingUserIter2 = matchingQueue.clnt_nickname_socket_map.find(matchedUser.userNickname2);
			matchingQueue.clnt_nickname_socket_map.erase(matchedUser.userNickname2);
			
			*/
		}

};




#endif // __MATCHING_H__
