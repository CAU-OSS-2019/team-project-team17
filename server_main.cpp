#include "matching_server.h"
#include "login_server.h"

int main(void){
	pthread_t t_id_login;
	LoginSocketServer loginSocketServer("server login socket", 9100, 1000);
	pthread_create(&t_id_login, NULL, loginSocketServer.handleLogin, (void*)NULL)

	pthread_t t_id_matching;
	MatchingSocketServer matchingSocketServer("server matching socket", 9000, 1000);
	pthread_create(&(t_id_matching), NULL, matchingSocketServer.handleMatching, (void*)NULL)
	
	
	
	return 0;
}
