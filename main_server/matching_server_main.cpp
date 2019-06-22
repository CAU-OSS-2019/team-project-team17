#include "matching_server.h"

int main(){
	
	
	GetCharacterInfo *info = new GetCharacterInfo();

	MatchingSocketServer matchingSocketServer("server matching socket",9000,1000);	
	map<best_pick_key,best_pick_value>::iterator iter;
int testcount=0;
	for(iter=info->best_pick_map.begin();iter!=info->best_pick_map.end();iter++){
	cout<<iter->first.character_name<<" "<<iter->first.rank<<" "<<iter->first.best_character<<" "<<iter->second.description<<" "<<iter->second.win_rate<<endl;
	//cout<<++testcount<<endl;
	}
	
//	for(iter=info->base_character_map.begin();iter!=info->base_character_map.end();iter++){
//	cout<<iter->first.character_name<<" "<<iter->first.rank<<" "<<iter->second<<endl;
//	}	
	matchingSocketServer.handleMatching(info);
}
