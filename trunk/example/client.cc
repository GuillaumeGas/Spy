#include <iostream>
#include "proto.hh"
#include "../Common/Client.hh"
#include "../Common/Client_session.hh"
#include "../Common/Message.hh"

using namespace std;


class session_on_client : public Client_session {

public:
    
    session_on_client(int socket) : Client_session(socket) {
	proto = new proto1(socket);
	proto->message["salut"]->sig_recv.connect(boost::bind(&session_on_client::salut, this, _1));
	proto->message["ERR"]->sig_recv.connect(boost::bind(&session_on_client::do_err, this, _1));
	proto->message["salut"]->operator()("1 2 3");
    }


    void do_err(string msg) {
	cout << "[SYS] -> ERR :! " << msg << endl;
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
	m_stop = false;
    }

};


int main(int argc, char ** argv) {
    Client <session_on_client> client(argc, argv);
    client.join();
}
