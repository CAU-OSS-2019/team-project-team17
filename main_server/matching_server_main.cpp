#include "matching_server.h"

int main(){
	
	
	GetCharacterInfo *info = new GetCharacterInfo();

	MatchingSocketServer matchingSocketServer("server matching socket",9000,1000);	
	
	matchingSocketServer.handleMatching(info);
}