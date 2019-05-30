#include "matching_server.h"

int main(){
	
	
	GetCharacterInfo *info = new GetCharacterInfo();

	
	info->getBaseCharacterInfo();
//	info->getBestPickCharacter();
        

	MatchingSocketServer matchingSocketServer("server matching socket",9100,1000);	
	
	matchingSocketServer.handleMatching();
}
