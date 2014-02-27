#include "Serv_session.hh"
#include <iostream>
#include "proto.hh"
#include "Message.hh"

using namespace std;


Serv_session::Serv_session(int sock) : Thread<Serv_session>(&Serv_session::session, this), Session(sock) {
    stop = false;
}


void Serv_session::loop_recv() {
    while ( ! stop ) {
	string msg;
	my_stream >> msg;
	if ( msg.length() != 0 ) {
	    bool trouve = false;
	    cout << msg << endl;
	    for ( auto it : message ) {
		if ( *(it.second) == msg ) {
		    it.second->sig_recv(wait(*it.second));
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
    Stream_net m(m_sock);
    int a;
    cin >> a;
    stop = true;
}

Serv_session::~Serv_session() {
    cout << " j'ecoute plus sur " << m_sock << endl;
    //quit(sock); pour plus tard
}
