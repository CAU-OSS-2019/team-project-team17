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
        	//findc=0;     
	       	cout<<"RUN ALGORITHM....."<<endl;
	      cout<<usersrc1.mynickname<<" "<<usersrc1.myposition<<" "<<usersrc1.duoposition<<" "<<usersrc1.rank<<endl;
		cout<<usersrc2.mynickname<<" "<<usersrc2.myposition<<" "<<usersrc2.duoposition<<" "<<usersrc2.rank<<endl;
            if(strcmp(usersrc1.myposition,usersrc2.duoposition)!=0|| strcmp(usersrc1.duoposition,usersrc2.myposition)!=0){
                cout<<"POSITION DOES NOT MATCH"<<endl;
		    return 0;//선호 포지션이 서로 맞지 않을경우 매칭 실패
            }
		cout<<"POSITION CHECK SUCCESSFUL"<<endl;
            int user1rank = getRanknum(usersrc1.rank);
            int user2rank = getRanknum(usersrc1.rank);

            if(user1rank-user2rank>=2 || user1rank-user2rank<=-2){//티어 차이가 2단계 이상일 경우
                cout<<"TIER DOES NOT MATCH"<<endl;
		    return 0;//매칭실패
            }
		cout<<"TIER CHECKED"<<endl;
            int avgrank = returnSmall(user1rank, user2rank);
		cout << "AVERAGE RANK : "<<getRankstr(avgrank)<<endl;
            user_character_info user1;
            user_character_info user2;
           
	    GetAllUserInfo * getAllUserInfo_obj_p1 = new GetAllUserInfo();
	    GetAllUserInfo * getAllUserInfo_obj_p2 = new GetAllUserInfo();
            
	    user1 = getAllUserInfo_obj_p1->getUserCharacterInfo(usersrc1.mynickname);
            user2 = getAllUserInfo_obj_p2->getUserCharacterInfo(usersrc2.mynickname);

            map<string_key, character_info>::iterator iter1;
            map<string_key, character_info>::iterator iter2;
		
            int compareNum = 0;
            double conformity = 0;
		//cout << "ITERATION START"<<endl;
            for(iter1 = user1.character.begin(); iter1 != user1.character.end(); iter1++){
		//cout<<(iter1->first).str<<endl;                
               // best_pick_value temp1 = getBestwinrate((iter1->first).str,(iter2->first).str,getRankstr(avgrank),info);
		//cout<<"getBsetWinRATE"<<endl;
                double basewinrate1 = getBasewinrate((iter1->first).str,getRankstr(avgrank).c_str(),info);

                double kdarate1 = getKDArate(iter1->second.kills,iter1->second.deaths,iter1->second.assist);

                double prob1 = (iter1->second.wins+iter1->second.losses)/(user1.wins+user1.losses);



                for(iter2 = user2.character.begin(); iter2 != user2.character.end(); iter2++){
                  // cout << (iter1->first).str << (iter2->first).str << endl; 
                   best_pick_value temp1 = getBestwinrate((iter1->first).str,(iter2->first).str,getRankstr(avgrank),info);
	       	   best_pick_value temp2 = getBestwinrate((iter2->first).str,(iter1->first).str,getRankstr(avgrank),info);
			if(strcmp(temp1.description,"Top")==0){
				strcpy(temp1.description,"탑");
			}
			if(strcmp(temp1.description,"Mid")==0){
				strcpy(temp1.description,"미드");
			}
			if(strcmp(temp1.description,"Jungler")==0){
				strcpy(temp1.description,"정글");
			}
			if(strcmp(temp1.description,"Support")==0){
				strcpy(temp1.description,"서포터");
			}
			if(strcmp(temp1.description,"AD Carry")==0){
				strcpy(temp1.description,"원딜");
			}
			
			if(strcmp(temp2.description,"Top")==0){
				strcpy(temp2.description,"탑");
			}
			if(strcmp(temp2.description,"Mid")==0){
				strcpy(temp2.description,"미드");
			}
			if(strcmp(temp2.description,"Jungler")==0){
				strcpy(temp2.description,"정글");
			}
			if(strcmp(temp2.description,"Support")==0){
				strcpy(temp2.description,"서포터");
			}
			if(strcmp(temp2.description,"AD Carry")==0){
				strcpy(temp2.description,"원딜");
			}
//		cout<<"유저1 캐릭 : "<<(iter1->first).str<<" 유저2 : "<<(iter2->first).str<<" "<<temp1.win_rate<< " "<<temp2.win_rate<<endl;	
                    if(strcmp(temp1.description,usersrc1.duoposition)!=0){//bestpickcharacter의 description과 자신이 희망하는 듀오의 포지션이
                                                                        //   일치하지 않으면 비교 대상 범주에 들어가지 않음
                    //    continue;
                    }

                    if(strcmp(temp2.description,usersrc2.duoposition)!=0){//마찬가지
                     //   continue;
                    }

                    
                    double basewinrate2 = getBasewinrate((iter2->first).str,getRankstr(avgrank).c_str(),info);

                    double kdarate2 = getKDArate(iter2->second.kills,iter2->second.deaths,iter2->second.assist);

                    double prob2 = (iter2->second.wins+iter2->second.losses)/(user2.wins+user2.losses);

                    double winrate1 = (iter1->second.wins)/(iter1->second.wins+iter1->second.losses);

                    double winrate2 = (iter2->second.wins)/(iter2->second.wins+iter2->second.losses);
                   //cout<<"base win rate = "<<basewinrate1<< " "<<basewinrate2<< " "<<temp1.win_rate<< " "<<temp2.win_rate<<" "<<winrate1<<" "<<winrate2<<endl; 
                    double interwinrate = basewinrate1+basewinrate2+temp1.win_rate+temp2.win_rate+winrate1+winrate2;
			double tempconform;
			tempconform = getConformity(interwinrate,kdarate1,kdarate2,(prob1+prob2)/2);
                    //conformity += getConformity(interwinrate,kdarate1,kdarate2,(prob1+prob2)/2);
		    conformity = conformity + tempconform;
		    //cout << "CONFORMITY = "<<tempconform<<endl;
                    compareNum++;
                }
            }
            conformity = conformity / compareNum;
		cout << "두 유저의 적합도 : "<<conformity<<endl;
          	//cout <<"FINDC:"<<findc<<endl;
	      	return conformity;

            // 디비에서 각 유저들 정보 꺼내와서
            // 알고리즘 돌리고
            // 그 결과(double 적합도)를 반환.
        }

        static double getConformity(double interwinrate, double kdarate1, double kdarate2, double prob){
		//cout <<"interrate : "<<interwinrate<<" kdasum : "<<kdarate1+kdarate2-6<<" prob : "<<(prob/100)+1<<endl;
		double result= ( (((interwinrate-100)/100)+1) * (( (kdarate1+kdarate2) / 100 ) + 1) *  ((prob/100)+1)  );
            //cout<<"result="<<result<<endl;
		if(result >= 999999){
		    result=0;
	    }
	    return result;

        }

        static double getKDArate(double kill, double death, double assist){

            return (kill+assist)/death;

        }


        static best_pick_value getBestwinrate(const char character_name[32], const char best_character_name[32], string ranknames, GetCharacterInfo *info){
            char rankname[32];
		//cout<<"RUN GETBSEWINRATE"<<endl;
            strcpy(rankname,ranknames.c_str());
		//cout<<"strcpy rankname"<<endl;
            best_pick_key tempkey;
	    //cout<<"declare tempkey"<<endl;
            strcpy(tempkey.best_character,best_character_name);
	    //cout<<"BESTNAME : "<<best_character_name<<endl;
	    //cout<<"strcpy tempkey.best"<<endl;
            strcpy(tempkey.rank,rankname);
	    //cout<<"strcpy tempkey.rank"<<endl;
            strcpy(tempkey.character_name,character_name);
		//cout<<"GET READY TO FINDING MAP"<<endl;
		//
	//	cout<<"tempkey = "<<tempkey.best_character<<" "<<tempkey.character_name<<" "<<tempkey.rank<<endl;
		if(strcmp(tempkey.rank,"Iron")==0){
	    		strcpy(tempkey.rank,"iron");
		}
		if(strcmp(tempkey.rank,"Bronze")==0){
	    		strcpy(tempkey.rank,"bronze");
		}
		if(strcmp(tempkey.rank,"Silver")==0){
	    		strcpy(tempkey.rank,"silver");
		}
		if(strcmp(tempkey.rank,"Gold")==0){
	    		strcpy(tempkey.rank,"gold");
		}
		if(strcmp(tempkey.rank,"Platinum")==0){
	    		strcpy(tempkey.rank,"platinum");
		}
		if(strcmp(tempkey.rank,"Diamond")==0){
	    		strcpy(tempkey.rank,"diamond");
		}		
		if(strcmp(tempkey.rank,"Master")==0){
	    		strcpy(tempkey.rank,"master");
		}
	    map<best_pick_key, best_pick_value >::iterator iter; //= info->best_pick_map.find(tempkey);
		
	    iter = info->best_pick_map.begin();

//		cout<<"map = "<<iter->first.best_character<<" "<<iter->first.character_name<<" "<<iter->first.rank<<endl;    
	    for(iter = info->best_pick_map.begin();iter!=info->best_pick_map.end();iter++){
	//	cout <<iter->first.rank<< " / "<<tempkey.rank<<endl;
			//cout << "MAP 탐색중 "<<iter->first.character_name<<" "<<iter->first.best_character<<" "<<iter->first.rank<<endl;
			
			if(strcmp(iter->first.character_name,tempkey.character_name)==0&&strcmp(iter->first.rank,tempkey.rank)==0&&strcmp(iter->first.best_character,tempkey.best_character)==0){
		   // cout<<"찾았습니다"<<endl;
		//   findc++;
		    //
		    //
		//if(iter!=info->best_pick_map.end()){
		//	cout<<"find 성공함"<<endl;
				return iter->second;
            }
			}
		//cout<<"find 실패함"<<endl;	
		        best_pick_value nullvalue;
        	    strcpy(nullvalue.description,"");
        	    nullvalue.win_rate=0;

        	    return nullvalue;
            }
	
            
        

        static double getBasewinrate(const char character_name[32],const char ranknames[32],GetCharacterInfo *info){
		

            char rankname[32];

            strcpy(rankname,ranknames);


            base_character_key tempkey;
            strcpy(tempkey.character_name, character_name);
            strcpy(tempkey.rank, rankname);
		
    		if(strcmp(tempkey.rank,"Iron")==0){
	    		strcpy(tempkey.rank,"iron");
		}
		if(strcmp(tempkey.rank,"Bronze")==0){
	    		strcpy(tempkey.rank,"bronze");
		}
		if(strcmp(tempkey.rank,"Silver")==0){
	    		strcpy(tempkey.rank,"silver");
		}
		if(strcmp(tempkey.rank,"Gold")==0){
	    		strcpy(tempkey.rank,"gold");
		}
		if(strcmp(tempkey.rank,"Platinum")==0){
	    		strcpy(tempkey.rank,"platinum");
		}
		if(strcmp(tempkey.rank,"Diamond")==0){
	    		strcpy(tempkey.rank,"diamond");
		}		
		if(strcmp(tempkey.rank,"Master")==0){
	    		strcpy(tempkey.rank,"master");
		}

	    map<base_character_key, float >::iterator iter;// = info->base_character_map.find(tempkey);
	
		//cout<<"tempkey="<<tempkey.character_name<<" "<<tempkey.rank<<" "<<iter->second<<endl;    
	    for(iter = info->base_character_map.begin();iter!=info->base_character_map.end();iter++){
			if(strcmp(iter->first.character_name,tempkey.character_name)==0&&strcmp(iter->first.rank,tempkey.rank)==0){	
//			cout<<"FIND"<<endl;
				return iter->second;
			}
		}	
	    return iter->second;
		
        }

        static int getRanknum(char rankname[32]){
            if(strcmp(rankname,"Iron")==0){
                return 0;
            } else if(strcmp(rankname,"Bronze")==0){
                return 1;
            } else if(strcmp(rankname,"Silver")==0){
                return 2;
            } else if(strcmp(rankname,"Gold")==0){
                return 3;
            } else if(strcmp(rankname,"Platinum")==0){
                return 4;
            } else if(strcmp(rankname,"Diamond")==0){
                return 5;
            } else if(strcmp(rankname,"Master")==0){
                return 6;
            } else if(strcmp(rankname,"Challenger")==0){
		return 7;
	    }
        }

        static string getRankstr(int ranknum){
            if(ranknum == 0) return "Iron";
            if(ranknum == 1) return "Bronze";
            if(ranknum == 2) return "Silver";
            if(ranknum == 3) return "Gold";
            if(ranknum == 4) return "Platinum";
            if(ranknum == 5) return "Diamond";
            if(ranknum == 6) return "Master";
	    if(ranknum == 7) return "Challenger";
        }


        static int returnSmall(int a, int b){
            if(a>b) return b;
            return a;
        }
};



#endif
