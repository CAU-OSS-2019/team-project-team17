#include "matching_server.h"

int main(){
	MatchingSocketServer matchingSocketServer("server matching socket",9000,1000);
	
	matchingSocketServer.handleMatching();
}
