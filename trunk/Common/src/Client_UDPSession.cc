#include "Client_UDPSession.hh"
#include "UDP_Message.hh"

using namespace std;

Client_UDPSession::Client_UDPSession( int & , int & , string & ) : Thread < Client_UDPSession >(&Client_UDPSession::loop_recv, this) {
    m_stop = false;
}

void Client_UDPSession::loop_recv() {
    this->sig_begin();
    while ( !m_stop ) {
	string msg;
	proto->waitmsg(msg);
	if ( msg.length() != 0 ) {
	    bool trouve = false;
	    for ( auto it : proto->message ) {
		if ( it.first == msg ) {
		    it.second->sig_recv( proto->wait(*it.second) );
		    break;
		}
	    }
	}
    }
    sig_end();
    cout << "quitter" << endl;
}


void Client_UDPSession::change_write_port( int port, string ip )  {
    proto->change_write_port(port, ip);
}
