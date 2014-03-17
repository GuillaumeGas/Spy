#include <iostream>
#include "proto.hh"

using namespace std;

class session_on_server : public Serv_session {

public:

    session_on_server(int socket) : Serv_session(socket) {
	proto = new proto1(socket);
	d = 727;
	(*proto)["OK"].sig_recv.connect ( boost::bind ( &session_on_server::ok, this, _1));
	(*proto)["RETOUR"].sig_recv.connect ( boost::bind( &session_on_server::do_retour,this, _1 ));
	(*proto)["salut"].sig_recv.connect(boost::bind (&session_on_server::do_salut, this,_1));
	begin.connect ( boost::bind ( &session_on_server::on_begin, this));
    }

    
    void on_begin () {
	int a = rand()%2000;
	m_value = expMod ( a , d, N );
	stringstream ss;
	ss << m_value;
	(*proto)["TEST"](ss.str());
    }

    void ok(string msg) {
	cout << " OK " << endl;
    }

    void do_retour ( string msg ) {
	stringstream ss(msg);
	int content;
	ss >> content;
	if ( m_value == expMod ( content, d, N )) {
	    state = (State_t)auth;
	    (*proto)["OK"]("");
	} else {
	    (*proto)["ERR"]("");
	    finish();
	}
    }


    void do_salut(string msg) {
	if ( state == auth ) {
	    stringstream ss(msg);
	    cout << "[CLIENT] -> Salut " << endl;

	} else {
	    (*proto)["ERR"]("");
	    finish();
	}
    }


    




private:
    int d;
    long m_value;
    State_t state;
};



int main(int argc, char ** argv) {
    srand(time(NULL));
    Server<session_on_server> serv(argc, argv);
    serv.start();
    serv.join();
}
