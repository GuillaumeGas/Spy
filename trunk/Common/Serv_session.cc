#include "Serv_session.hh"
#include <iostream>

#include "Message.hh"

using namespace std;


Serv_session::Serv_session(int sock) : Thread<Serv_session>(&Serv_session::session, this) {
    stop = false;
}


void Serv_session::loop_recv() {
    while ( ! stop ) {
	string msg;
	proto->my_stream >> msg;
	if ( msg.length() != 0 ) {
	    bool trouve = false;
	    cout << msg << endl;
	    for ( auto it : proto->message ) {
		if ( *(it.second) == msg ) {
		    it.second->sig_recv(proto->wait(*it.second));
		}
	    }
	} else {
	    stop = true;
	}
    }
    cout << "dommage" << endl;
}



void Serv_session::session() {
    other(&Serv_session::loop_recv);
}

Serv_session::~Serv_session() {
    cout << " j'ecoute plus sur " << proto->m_sock << endl;
    //quit(sock); pour plus tard
}
