#include "Serv_session.hh"
#include <iostream>
#include "Message.hh"
#include "Stream_net.hh"
#include "proto.hh"

using namespace std;

Serv_session::Serv_session(int sock) : Thread<Serv_session>(&Serv_session::session, this) {
    m_sock = sock;
    stop = false;
}


void Serv_session::loop_recv() {

    while ( not stop ) {
	Stream_net m(m_sock);
	string msg;
	m >> msg;
	if ( msg.length() != 0 ) {
	    cout <<"[" << m_sock << "] -> " <<  msg << endl;    
	} else {
	    stop = true;
	}
    }
    cout << "dommage" << endl;
}

void Serv_session::session() {
    other(&Serv_session::loop_recv);
    Stream_net m(m_sock);
    Message<int, string> message("message", "1i1s");
    message.sig_send.connect(message1);
    message(m ,1, "salut");
    int a;
    cin >> a;
    stop = true;
}

Serv_session::~Serv_session() {
    cout << " j'ecoute plus sur " << m_sock << endl;
    //quit(sock); pour plus tard
}
