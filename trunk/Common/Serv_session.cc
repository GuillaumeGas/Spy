#include "Serv_session.hh"
#include <iostream>
#include "Stream_net.hh"
#include "proto.hh"

using namespace std;


Serv_session::Serv_session(int sock) : Thread<Serv_session>(&Serv_session::session, this) {
    m_sock = sock;
    stop = false;
    message["message"] = "1i1s";
    sig_msg["message"] = new signal<void(string)> ;
    sig_msg["message"]->connect(foo);
    message["m2"] = "1i";
    sig_msg["m2"] = new signal<void(string)> ;
    message["m3"] = "5c";
    sig_msg["m3"] = new signal<void(string)> ;
}






string Serv_session::wait(string msg, Stream_net & s) {
    stringstream total("");
    string format = message.find(msg)->second;
    for ( int i = 0 ; i < format.length() ; i++ ) {
	if ( format[i] <= '9' && format[i] >= '0' ) {
	    for ( int j = 0 ; j < format[i] - '0' ; i++ ) {
		switch(format[i + 1]) {
		case 'i': int a;
		    s >> a;
		    total << a << " "; break;
		case 'c': char c;
		    s >> c;
		    cout << c << endl;
		    total << c << " "; break;
		case 's': string msg;
		    s >> msg;
		    total << msg << " "; break;
		}
	    }
	}
    }
    return total.str();  
}


void Serv_session::loop_recv() {
    while ( ! stop ) {
	Stream_net m(m_sock);
	string msg;
	m >> msg;
	if ( msg.length() != 0 ) {
	    bool trouve = false;
	    cout << msg << endl;
	    for ( auto it : message ) {
		if ( it.first == msg ) {
		    auto it = sig_msg.find(msg);
		    if ( it != sig_msg.end() ) {
			it->second->operator()(wait(msg, m));
		    }

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
