#include <iostream>
#include "proto.hh"
#include "../Net.hh"
using namespace std;


class session_on_client : public Client_session {

public:
    
    session_on_client(int socket) : Client_session(socket) {
	proto = new proto1(socket);
	(*proto)["OK"].sig_recv.connect ( boost::bind ( &session_on_client::do_ok, this, _1));
	(*proto)["ERR"].sig_recv.connect ( boost::bind ( &session_on_client::do_err, this, _1));
	(*proto)["TEST"].sig_recv.connect ( boost::bind ( &session_on_client::do_test, this, _1));
    }


    void do_err(string msg) {
	cout << "[SYS] -> ERR :! " << endl;
    }
    
    void do_ok(string msg ){
	cout << "[SYS] -> OK :! " << endl;
	(*proto)["salut"]("");
    }
    
    void do_test ( string msg ) {
	int content;
	stringstream ss(msg);
	ss >> content;
	content = expMod ( content, e, N);
	stringstream ss2;
	ss2 << content;
	(*proto)["RETOUR"](ss2.str());
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


    void do_img ( string img, int h, int l ) {
	cout << "image de " << h << " * " << l << "contenant " << img << endl; 
    }



};


int main(int argc, char ** argv) {
    Client <session_on_client> client(argc, argv);
    client.join();
}
