#ifndef __STRUCT__
#define __STRUCT__


#include <string>
#include <iostream>
#include <string.h>
#include <map>

using namespace std;


typedef struct LoginSocketInfo{
	int clnt_socket;
	string id;
	string pwd;
}login_socket_info;

typedef struct LoginInfo{
	string id;
	string pwd;
}login_info;

typedef struct SourceOfMatchingS{ //소켓 추가
	string mynickname;
	string myposition;
	string duoposition;
	string rank;
	int clnt_sock;
}source_of_matching_s;

typedef struct UserGameInfo {

	string nickname;
	string rank;
	
}user_game_info;

// To do : data를 string으로 했을 때 다루는 것 해보기.
typedef struct ResultOfMatching{// 매칭 결과는 상대 닉네임, 상대 랭크, 적합도 3가지이다.
	string duonickname;
	string duorank;
	int conformity;
}result_of_matching;


typedef struct singupInfo{
	string id;
	string pwd;
	string nickname;
}signup_info;

typedef struct CharacterInfo {
	int wins;
	int losses;
	float kills;
	float deaths;
	float assist;
}character_info;

typedef struct UserCharacterInfo {
	string rank;
	float wins;
	float losses;
	string my_pref_pos;
	string duo_pref_pos;
	map<string, character_info> character;
	
}user_character_info;


typedef struct UserInfo {

	string nickname;
	string id;
	string pwd;

}user_info;


typedef struct SourceOfMatching{
	string mynickname;
	string myposition;
	string duoposition;
	string rank;
}source_of_matching;



typedef struct MatchingQueue{
	int clnt_cnt = 0;
	map< string, source_of_matching_s > clnt_nickname_socket_map;

}matching_queue;

typedef struct matchedUser{
	string userNickname1;
	//result_of_matching userInfo1;
	int userInfo1;

	string userNickname2;
	//result_of_matching userInfo2;
	int userInfo2;

}matched_user;


#endif