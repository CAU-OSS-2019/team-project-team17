#ifndef __MATCHING_H__
#define __MATCHING_H__

#include "socket_server.h"
#include "algorithm.h"


using namespace std;

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
			string userNickname[10];
			map< string, int >::iterator iter;
			
			for(iter = (matchingQueue.clnt_nickname_socket_map).begin();
				iter != (matchingQueue.clnt_nickname_socket_map).end() && i <10;
					 ++i, ++iter){
				userNickname[i] = iter->second;
			}
			
			return compareConformity(userNickname);
			
		}
		

		matched_user compareConformity(string userNickname[]){
			double userConformity[10][9];
			
			double max = 0;
			int maxI =0, maxJ =0;
			
			userConformity[0][0] = -1;
			max = runAlgorithm(userNickname[0], userNickname[1]);
			for(int i = 0; i < 10; i++){
				for(int j = i+1; j < 10; j++){
					userConformity[i][j] = Algorithm::runAlgorithm(userNickname[i], userNickname[j], usersrc1, usersrc2);
					
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
		}
		
		void handleMatching(void){
			int thread_create_success = -1;
			mutexInit();

			pthread_mutex_lock(&matching_mutex);
			while(1){
				acceptClient();
				
				pthread_mutex_lock(&matching_queue_mutex);
				
				char buffer[31];
				
				// sizeof(buffer) 크기 측정해보기. 4byte로 나오면 안됨.
				if(read(clnt_sock, buffer, sizeof(buffer)) == -1){
					cout << "Error : server -- read() in handleMatching()."<<endl;
					close(clnt_sock);
				}

				string buffer_s(buffer);
				matchingQueue.clnt_nickname_socket_map.insert(make_pair(buffer_s, clnt_sock));

				matchingQueue.clnt_cnt++;
				
				if(matchingQueue.clnt_cnt == 10){
					// memory 낭비 없애려면 동적 할당으로 구현해도 될 듯.
					Matching * matching = new Matching(matchingQueue);
					matched_user matchedUser = matching->runMatching();
					delete matching;

					sendData(matchedUser);
					removeMatchedUserFromQueue(matchedUser);
					
				}
				pthread_mutex_unlock(&matching_queue_mutex);
				
				
			}
			pthread_mutex_unlock(&matching_mutex);


		}

		void sendData(matched_user matchedUser){
			cout << "server --- sendData() run. "<<endl;
			
			//되는지 확인해보기 맵에서 값 접근 방법 -  a[1] 접근
			map< string, int >::iterator matchingUserIter1;
			map< string, int >::iterator matchingUserIter2;
			matchingUserIter1 = matchingQueue.clnt_nickname_socket_map.find(matchedUser.userNickname1);
			matchingUserIter2 = matchingQueue.clnt_nickname_socket_map.find(matchedUser.userNickname2);
			int userSock1 = matchingUserIter1->second;
			int userSock2 = matchingUserIter2->second;

			write(userSock1, &matchedUser.userInfo1, sizeof(matchedUser.userInfo1));
			write(userSock2, &matchedUser.userInfo2, sizeof(matchedUser.userInfo2));

		}

		void mutexInit(void){
			pthread_mutex_init(&matching_mutex, NULL);
			pthread_mutex_init(&matching_queue_mutex, NULL);
		}

		void removeMatchedUserFromQueue(matched_user matchedUser){
			// nickname에 해당하는 것 있는 키 값 얻어서 그 부분 없앰. sockets에서도 그 인덱스 부분 없앰. 
		}

};




#endif // __MATCHING_H__
