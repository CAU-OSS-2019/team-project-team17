#include "login_server.h"

int main(void){
	pthread_t t_id_login;
	LoginSocketServer loginSocketServer("server login socket", 9100, 1000);
	int err = pthread_create(&t_id_login, NULL, LoginSocketServer::handleLogin, &loginSocketServer);

	pthread_t t_id_matching;
	MatchingSocketServer matchingSocketServer("server matching socket", 9000, 1000);
	int err2=pthread_create(&t_id_matching, NULL, MatchingSocketServer::handleMatching, &matchingSocketServer);
	
	
	return 0;
}
