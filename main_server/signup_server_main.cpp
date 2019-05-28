#include "signup_server.h"

using namespace std;


int main(){
	SignupSocketServer signupSocketServer("signup server socket",9200,1000);

	signupSocketServer.handleSignup();
}
