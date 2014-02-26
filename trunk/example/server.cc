#include <iostream>
#include "../Common/Server.hh"
#include "../Common/Serv_session.hh"
using namespace std;

class session_on_server : public Serv_session {

public:

    session_on_server(int socket) : Serv_session(socket) {
	message["salut"] = "1s";
	sig_msg["salut"] = new signal<void(string)>;
	sig_msg["salut"]->connect(boost::bind(&session_on_server::salut, this, _1));
    }
    
    void salut(string msg) {
	stringstream ss(msg);
	int value;
	ss >> value;
	cout << "recu " << value << endl;
    }

private:

};



int main(int argc, char ** argv) {
    Server<session_on_server> serv(argc, argv);
    serv.start();
}
