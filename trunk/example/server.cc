#include <iostream>
#include "../Common/Server.hh"
#include "../Common/Serv_session.hh"
#include "../Common/Message.hh"
using namespace std;

class session_on_server : public Serv_session {

public:

    session_on_server(int socket) : Serv_session(socket) {
	message["salut"] = new Message("salut", "1s3i", this);
	message["salut"]->sig_recv.connect(boost::bind(&session_on_server::salut, this, _1));
	message["salut"]->operator()("1 2 4");
    }


    
    void salut(string msg) {
	stringstream ss(msg);
	int value;
	ss >> value;
	cout << "recu " << value << " ";
	ss >> value;
	cout << value << " ";
	ss >> value;
	cout << value << " " << endl;
    }




private:

};



int main(int argc, char ** argv) {
    Server<session_on_server> serv(argc, argv);
    serv.start();
}
