#include "../include/Serv_session.hh"
#include <iostream>

#include "../include/Message.hh"
#include "../include/Img_Message.hh"

using namespace std;


Serv_session::Serv_session(int sock) : Thread<Serv_session>(&Serv_session::session, this) {
    stop = false;
}


void Serv_session::loop_recv() {
    begin();
    while ( ! stop ) {
	string msg;
	proto->my_stream >> msg;
	if ( msg.length() != 0 ) {
	    bool trouve = false;
	    for ( auto it : proto->message ) {
		if ( it.first == msg ) {
		    it.second->recv ( );
		    cout << "[INFO] -> " << msg << " recv" << endl;
		}
		
	    }
	    for ( auto it : proto->imessage ) {
		if ( it.first == msg ) {
		    it.second->recv( );
		}
	    }
	} else {
	    stop = true;
	}
    }
    end();
    cout << "[INFO] -> client quit" << endl;
}



void Serv_session::session() {
    other(&Serv_session::loop_recv);
}

Serv_session::~Serv_session() {
    //quit(sock); pour plus tard
}
