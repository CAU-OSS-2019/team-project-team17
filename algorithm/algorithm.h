#ifndef __ALGORITHM__
#define __ALGORITHM__


#include <iostream>
#include <string>
#include "../main_server/db/getAllUserInfo.h"
#include "../main_server/db/getCharacterInfo.h"
#include <map>
#include "../structs/struct.h"


using namespace std;

class Algorithm{

    public:

        static double runAlgorithm(source_of_matching_s usersrc1, source_of_matching_s usersrc2, GetCharacterInfo *info){
                
            if(strcmp(usersrc1.myposition,usersrc2.duoposition)!=0|| strcmp(usersrc1.duoposition,usersrc2.myposition)!=0){
                return 0;//선호 포지션이 서로 맞지 않을경우 매칭 실패
            }

            int user1rank = getRanknum(usersrc1.rank);
            int user2rank = getRanknum(usersrc1.rank);

            if(user1rank-user2rank>=2 || user1rank-user2rank<=-2){//티어 차이가 2단계 이상일 경우
                return 0;//매칭실패
            }

            int avgrank = returnSmall(user1rank, user2rank);

            user_character_info user1;
            user_character_info user2;
           
	    GetAllUserInfo * getAllUserInfo_obj_p1 = new GetAllUserInfo();
	    GetAllUserInfo * getAllUserInfo_obj_p2 = new GetAllUserInfo();
            
	    user1 = getAllUserInfo_obj_p1->getUserCharacterInfo(usersrc1.mynickname);
            user2 = getAllUserInfo_obj_p2->getUserCharacterInfo(usersrc2.mynickname);

            map<char[32], character_info>::iterator iter1;
            map<char[32], character_info>::iterator iter2;

            int compareNum = 0;
            double conformity = 0;

            for(iter1 = user1.character.begin(); iter1 != user1.character.end(); iter1++){
                
                best_pick_value temp1 = getBestwinrate(iter1->first,iter2->first,getRankstr(avgrank),info);

                double basewinrate1 = getBasewinrate(iter1->first,getRankstr(avgrank),info);

                double kdarate1 = getKDArate(iter1->second.kills,iter1->second.deaths,iter1->second.assist);

                double prob1 = (iter1->second.wins+iter1->second.losses)/(user1.wins+user1.losses);



                for(iter2 = user2.character.begin(); iter2 != user2.character.end(); iter2++){
                    
                    best_pick_value temp2 = getBestwinrate(iter2->first,iter1->first,getRankstr(avgrank),info);

                    if(strcmp(temp1.description,usersrc1.duoposition)!=0){//bestpickcharacter의 description과 자신이 희망하는 듀오의 포지션이
                                                                        //   일치하지 않으면 비교 대상 범주에 들어가지 않음
                        continue;
                    }

                    if(strcmp(temp2.description,usersrc2.duoposition)!=0){//마찬가지
                        continue;
                    }

                    
                    double basewinrate2 = getBasewinrate(iter2->first,getRankstr(avgrank),info);

                    double kdarate2 = getKDArate(iter2->second.kills,iter2->second.deaths,iter2->second.assist);

                    double prob2 = (iter2->second.wins+iter2->second.losses)/(user2.wins+user2.losses);

                    double winrate1 = (iter1->second.wins)/(iter1->second.wins+iter1->second.losses);

                    double winrate2 = (iter2->second.wins)/(iter2->second.wins+iter2->second.losses);
                    
                    double interwinrate = basewinrate1+basewinrate2+temp1.win_rate+temp2.win_rate+winrate1+winrate2;

                    conformity += getConformity(interwinrate,kdarate1,kdarate2,(prob1+prob2)/2);
                    compareNum++;
                }
            }
            conformity = conformity / compareNum;

            return conformity;

            // 디비에서 각 유저들 정보 꺼내와서
            // 알고리즘 돌리고
            // 그 결과(double 적합도)를 반환.
        }

        static double getConformity(double interwinrate, double kdarate1, double kdarate2, double prob){

            return ( (((interwinrate-200)/100)+1) * (( (kdarate1+kdarate2-6) / 100 ) + 1) *  ((prob/100)+1)  );

        }

        static double getKDArate(double kill, double death, double assist){

            return (kill+assist)/death;

        }


        static best_pick_value getBestwinrate(char character_name[32], char best_character_name[32], char rankname[32], GetCharacterInfo *info){

            best_pick_key tempkey;
            strcpy(tempkey.best_character,best_character_name);
            strcpy(tempkey.rank,rankname);
            strcpy(tempkey.character_name,character_name);
		
	    map<best_pick_key, best_pick_value >::iterator iter =
		    info->best_pick_map.find(tempkey);

            if(iter!=info->best_pick_map.end()){
                return iter->second;
            } else {
		
		        best_pick_value nullvalue;
        	    strcpy(nullvalue.description,"");
        	    nullvalue.win_rate=0;

        	    return nullvalue;
            }
            
        }

        static double getBasewinrate(char character_name[32], char rankname[32],GetCharacterInfo *info){

            base_character_key tempkey;
            strcpy(tempkey.character_name, character_name);
            strcpy(tempkey.rank, rankname);
		
	    map<base_character_key, float >::iterator iter
		    = info->base_character_map.find(tempkey);
	
	
	    return iter->second;
		
        }

        static int getRanknum(string rankname){
            if(strcmp(rankname,"iron")==0){
                return 0;
            } else if(strcmp(rankname,"bronze")==0){
                return 1;
            } else if(strcmp(rankname,"silver")==0){
                return 2;
            } else if(strcmp(rankname,"gold")==0){
                return 3;
            } else if(strcmp(rankname,"platinum")==0){
                return 4;
            } else if(strcmp(rankname,"diamond")==0){
                return 5;
            } else if(strcmp(rankname,"master")==0){
                return 6;
            }
        }

        static string getRankstr(int ranknum){
            if(ranknum == 0) return "iron";
            if(ranknum == 1) return "bronze";
            if(ranknum == 2) return "silver";
            if(ranknum == 3) return "gold";
            if(ranknum == 4) return "platinum";
            if(ranknum == 5) return "diamond";
            if(ranknum == 6) return "master";
        }


        static int returnSmall(int a, int b){
            if(a>b) return b;
            return a;
        }
};



#endif
