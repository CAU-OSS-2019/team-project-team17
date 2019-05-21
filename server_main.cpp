#include "matching_server.h"

int main(void){
	MatchingSocketServer matchingSocketServer("server matching socket", 8888, 1000);
	matchingSocketServer.handleMatching();
	
	
	
	return 0;
}
