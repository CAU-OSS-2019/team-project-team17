#include "signup_server.h"
#include "../structs/struct.h"

using namespace std;


int main(){
	cout << sizeof(signup_info) <<endl;
	SignupSocketServer signupSocketServer("signup server socket",9200,1000);

	signupSocketServer.handleSignup();
}
