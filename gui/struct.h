#ifndef STRUCT_H
#define STRUCT_H

#include <string>
#include <iostream>
#include <string.h>
#include <map>

using namespace std;


typedef struct LoginData{
    char nickname[32];
    char rank[32];
    bool loginSuccess;
}login_data;

typedef struct LoginSocketInfo{
    int clnt_socket;
    char id[32];
    char pwd[32];
}login_socket_info;

typedef struct LoginInfo{
    char id[32];
    char pwd[32];
}login_info;

typedef struct SourceOfMatchingS{ //소켓 추가
    char mynickname[32];
    char myposition[32];
    char duoposition[32];
    char rank[32];
    int clnt_sock;

    bool operator<(const SourceOfMatchingS& k) const {

        if (clnt_sock < k.clnt_sock)
            return true;
        else if (clnt_sock > k.clnt_sock)
            return false;

        if (mynickname < k.mynickname)
            return true;
        else if (mynickname > k.mynickname)
            return false;

        if (rank < k.rank)
            return true;
        else if (rank > k.rank)
            return false;

        if (myposition < k.myposition)
            return true;
        else
            return false;

        if (duoposition < k.duoposition)
            return true;
        else
            return false;
    }


}source_of_matching_s;

typedef struct UserGameInfo {

    char nickname[32];
    char rank[32];

}user_game_info;

// To do : data를 char으로 했을 때 다루는 것 해보기.
typedef struct ResultOfMatching{// 매칭 결과는 상대 닉네임, 상대 랭크, 적합도 3가지이다.
    char duonickname[32];
    char duorank[32];
    double conformity;
}result_of_matching;


typedef struct singupInfo{
    char id[32];
    char pwd[32];
    char nickname[32];
}signup_info;

typedef struct CharacterInfo {
    int wins;
    int losses;
    float kills;
    float deaths;
    float assist;
}character_info;

typedef struct UserCharacterInfo {
    char rank[32];
    float wins;
    float losses;
    char my_pref_pos[32];
    char duo_pref_pos[32];
    map<char, character_info> character;

}user_character_info;


typedef struct UserInfo {

    char nickname[32];
    char id[32];
    char pwd[32];

}user_info;


typedef struct SourceOfMatching{
    char mynickname[32];
    char myposition[32];
    char duoposition[32];
    char rank[32];

    bool operator<(const SourceOfMatching& k) const {

        if (mynickname < k.mynickname)
            return true;
        else if (mynickname > k.mynickname)
            return false;

        if (rank < k.rank)
            return true;
        else if (rank > k.rank)
            return false;

        if (myposition < k.myposition)
            return true;
        else
            return false;

        if (duoposition < k.duoposition)
            return true;
        else
            return false;
    }

}source_of_matching;



typedef struct MatchingQueue{
    int clnt_cnt = 0;
    map< char, source_of_matching_s > clnt_nickname_socket_map;

}matching_queue;

typedef struct matchedUser{
    result_of_matching res1;
    result_of_matching res2;

}matched_user;

typedef struct BestPickKey {
    char character_name[32];
    char rank[32];
    char best_character[32];

    bool operator<(const BestPickKey& k) const {

        if (character_name < k.character_name)
            return true;
        else if (character_name > k.character_name)
            return false;

        if (rank < k.rank)
            return true;
        else if (rank > k.rank)
            return false;

        if (best_character < k.best_character)
            return true;
        else
            return false;
    }


}best_pick_key;

typedef struct BestPickValue {
    float win_rate;
    char description[32];


}best_pick_value;

typedef struct BaseCharacterKey {
    char character_name[32];
    char rank[32];

    bool operator<(const BaseCharacterKey& k) const {

        if (character_name < k.character_name)
            return true;
        else if (character_name > k.character_name)
            return false;

        if (rank < k.rank)
            return true;
        else
            return false;
    }

}base_character_key;

#endif // STRUCT_H
