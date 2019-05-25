#include "login_server.h"

using namespace std;


int main(){
	LoginSocketServer loginSocketServer("server login socket",9000,1000);

	loginSocketServer.handleLogin();
}
