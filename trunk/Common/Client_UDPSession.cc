#include "Client_UDPSession.hh"
#include "UDP_Message.hh"

using namespace std;

Client_UDPSession::Client_UDPSession( sockaddr_in sin ) : Thread < Client_UDPSession >(&Client_UDPSession::loop_recv, this) {
    m_sin = sin;
    m_stop = false;
    start();
}



void Client_UDPSession::loop_recv() {
    this->begin();
    while ( !m_stop ) {
	string msg;
	proto->waitmsg(msg);
	cout << msg << endl;
	if ( msg.length() != 0 ) {
	    bool trouve = false;
	    /*	    for ( auto it : proto->message ) {
		    if ( it.first == msg ) {
		    //it.second->sig_recv( proto->wait(*it.second) );
		    }
		    }
		    } else {
		    m_stop = true;
		    }*/
	}
    }
    end();
    cout << "quitter" << endl;
}
