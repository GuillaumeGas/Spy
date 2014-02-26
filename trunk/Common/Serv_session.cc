#include "Serv_session.hh"
#include <iostream>
#include "proto.hh"

using namespace std;


Serv_session::Serv_session(int sock) : Thread<Serv_session>(&Serv_session::session, this), my_stream(sock) {
    m_sock = sock;
    stop = false;
}



void Serv_session::send_msg(string msg, string content) {
    stringstream ss(content);
    string format = message.find(msg)->second;
    my_stream << format.c_str() << msg.c_str();
    for ( int i = 2 ; i < format.length() ; i++ ) {
	if ( format[i] <= '9' && format[i] >= '0' ) {
	    for ( int j = 0 ; j < format[i] - '0' ; j++ ) {
		switch( format[i + 1] ) {
		case 'i' : int a;
		    if ( !ss.eof() ) {
			ss >> a;
			my_stream << a;
		    }
		    break;
		case 'c': char c;
		    if ( !ss.eof() ) {
			ss >> c;
			my_stream << c;
		    } 
		    break;
		case 's': string m;
		    if ( !ss.eof() ) {
			ss >> m;
			my_stream << m.c_str();
		    }
		    break;
		}
	    }
	}
    }
    if ( !my_stream.send() ) {
	cout << "[ERROR] -> message mal forme" << endl;
	my_stream.clean();
    }
}

string Serv_session::wait(string msg) {
    stringstream total("");
    string format = message.find(msg)->second;
    for ( int i = 0 ; i < format.length() ; i++ ) {
	if ( format[i] <= '9' && format[i] >= '0' ) {
	    for ( int j = 0 ; j < format[i] - '0' ; i++ ) {
		switch(format[i + 1]) {
		case 'i': int a;
		    my_stream >> a;
		    total << a << " "; break;
		case 'c': char c;
		    my_stream >> c;
		    cout << c << endl;
		    total << c << " "; break;
		case 's': string m;
		    my_stream >> m;
		    total << m << " "; break;
		}
	    }
	}
    }
    return total.str();  
}


void Serv_session::loop_recv() {
    while ( ! stop ) {
	string msg;
	my_stream >> msg;
	if ( msg.length() != 0 ) {
	    bool trouve = false;
	    cout << msg << endl;
	    for ( auto it : message ) {
		if ( it.first == msg ) {
		    auto it = sig_msg.find(msg);
		    if ( it != sig_msg.end() ) {
			it->second->operator()(wait(msg));
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
