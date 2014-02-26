#include "Serv_session.hh"
#include <iostream>
#include "Stream_net.hh"
#include "proto.hh"

using namespace std;

Serv_session::Serv_session(int sock) : Thread<Serv_session>(&Serv_session::session, this) {
    m_sock = sock;
    stop = false;
    message["message"] = "1i1s";
}

void Serv_session::wait(string msg, Stream_net & s) {
    
}


void Serv_session::loop_recv() {
    while ( ! stop ) {
	Stream_net m(m_sock);
	string msg;
	m >> msg;
	if ( msg.length() != 0 ) {
	    bool trouve = false;
	    for ( auto it : message ) {
		if ( it.first == msg ) {
		    wait(msg, m);
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
