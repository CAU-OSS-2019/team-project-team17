
#ifndef __MATCHING_H__
#define __MATCHING_H__

#include "socket_server.h"

using namespace std;
/*
typedef struct LoginQueue{
	int clnt_cnt = 0;
	map< string, int > clnt_id_socket_map;
	map< int, string > clnt_socket_pwd_map;

}login_queue;
*/

typedef struct LoginSocketInfo{
	int clnt_socket;
	string id;
	string pwd;
}login_socket_info;

typedef struct LoginInfo{
	string id;
	string pwd;
}login_info;

class Login{
	private:
		matching_queue loginQueue;

	public:
		//Constructor
		Login(login_queue loginQueueInput)
			: loginQueue(loginQueueInput){}
		
		/* start matching */
		bool runLogin(void){
			cout<<"runLogin"<<endl;
			// 로그인 데이터 받은 것을 바탕으로 
			int i = 0;
			string userNickname[MATCHING_QUEUE_SIZE];
			map< string, int >::iterator iter;
			
			for(iter = (matchingQueue.clnt_nickname_socket_map).begin();
				iter != (matchingQueue.clnt_nickname_socket_map).end() && i <MATCHING_QUEUE_SIZE;
					 ++i, ++iter){
				userNickname[i] = iter->second;
			}
			
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




class LoginSocketServer : public SocketServer{
	
	/* google style */
	public :
		int receive_success;
		int send_success;
		//login_queue loginQueue;


	public :
		/* IF TO DO : server_ip[] 에서 오류나면 스트링으로 바꾸고 스트링으로 서버 주소
		 *  받아서 나중에 사용할때 char *로 변환 해줄 것. */
		LoginSocketServer(string socket_name, int open_port, int clnt_listen_cnt)
			: SocketServer(socket_name, open_port, clnt_listen_cnt){

			this -> prepareServerSocket();
			cout << "prepare login "<<endl;
		}
		
		void handleLogin(void){

			while(1){
				acceptClient();
				cout << "accept()" << endl;
				cout << "connect" <<endl;	
				
				/*
				string buffer_s;
				
				if(read(clnt_sock, &buffer_s, sizeof(buffer_s)) == -1){
					cout << "Error : server -- read() in handleMatching()."<<endl;
					cout << "kyeong tae" <<endl;
					close(clnt_sock);
				}
				*/

				/*
				char buffer[31];
				
				// sizeof(buffer) 크기 측정해보기. 4byte로 나오면 안됨.
				if(read(clnt_sock, buffer, sizeof(buffer)) == -1){
					cout << "Error : server -- read() in handleMatching()."<<endl;
					close(clnt_sock);
				}

				string buffer_s(buffer);
				*/
				login_info loginInfo;

				if(read(clnt_sock, &loginInfo, sizeof(loginInfo)) == -1){
					cout << "Error : server -- read() in handleLogin()."<<endl;
					close(clnt_sock);
				}
				
				login_socket_info loginSocketInfo;
				
				loginSocketInfo.clnt_sock = clnt_sock;
				loginSocketInfo.id = loginInfo.id;
				loginSocketInfo.pwd = loginInfo.pwd;

				/*
				loginQueue.clnt_id_socket_map.insert(make_pair(loginInfo.id, clnt_sock));
				loginQueue.clnt_socket_pwd_map.insert(make_pair(clnt_sock, loginInfo.pwd));
				matchingQueue.clnt_cnt++;
				*/

				pthread_create(&t_id, NULL, loginClnt, (void*)&loginSocketInfo);

				// 사실 멀티쓰레딩 돌려야 함. 로그인 실패 보내주고 다시 하려면.	


				pthread_mutex_unlock(&matching_queue_mutex);
				
				
			}
			pthread_mutex_unlock(&matching_mutex);


		}

		void * loginClnt(void * loginSocketInfo_arg){
			login_socket_info loginSocketInfo = *((login_socket_info *)loginSocketInfo_arg);
			
			int clnt_sock = loginSocketInfo.clnt_sock;
			string id = loginSocketInfo.id;
			string pwd = loginSocketInfo.pwd;




			
			if(loginSuccess){
				sendLoginData(true);
				removeLoginedUserFromQueue(loginQueue);
			}
			
			else{
				sendLoginData(false);
				removeLoginedUserFromQueue(loginQueue);
				
			}
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
