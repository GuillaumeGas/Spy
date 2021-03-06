#include "../include/Client_session.hh"
#include "../include/Message.hh"
#include "../include/Img_Message.hh"

using namespace std;

Client_session::Client_session(int _sock) : Thread<Client_session>(&Client_session::loop_recv, this) {
  m_sock = _sock;
  m_stop = false;
  auth = false;
}

void Client_session::loop_recv() {
    this->begin();
    while ( !m_stop ) {
	string msg;
	proto->my_stream >> msg;
	if ( msg.length() != 0 ) {
	    bool trouve = false;
	    for ( auto it : proto->message ) {
		if ( it.first == msg ) {
		    it.second->recv( );
		}
	    }
	    for ( auto it : proto->imessage ) {
		if ( it.first == msg ) {
		    it.second->recv( );
		}
	    }
	} else {
	    m_stop = true;
	}
    }
    end();
    cout << " quitter" << endl;
}

int Client_session::get_sock()const {
  return m_sock;
}

bool Client_session::IsStopped()const {
  return m_stop;
}

void Client_session::set_stop() {
  m_stop = !m_stop;
}

void Client_session::finish() {
    m_stop = true;
}
