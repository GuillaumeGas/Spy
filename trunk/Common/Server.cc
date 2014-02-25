#include "Server.hh"
#include <iostream>
using namespace std;


Server::Server(int argc, char ** argv) {
    load_port(argc, argv);
    init_sock();
    init_addr();
    do_bind();
    do_listen();
}


void Server::start() {
    loop_accept();
}


void Server::loop_accept() {
    socklen_t size_addr = sizeof(sin);
    while ( 1 ) {
	int client = accept( m_sock, (sockaddr *)&sin, &size_addr);
	if ( client != - 1 ) {
	    cout << "[INFO] -> nouveau client " << endl;
	}
    }
}



void Server::do_bind() {
    if ( bind( m_sock, (sockaddr *) &sin, sizeof(sin)) == -1 ) {
	cout << "Probleme de bind changer de Port" << endl;
	throw m_port;
    }
}

void Server::do_listen() {
    if ( listen( m_sock, 0 ) == -1 ) {
	cout << "Probleme de listen changer de Pc" << endl;
	throw m_sock;
    }
}


void Server::init_addr() {
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(m_port);
}

void Server::init_sock() {
    m_sock = socket(AF_INET, SOCK_STREAM, 0);
}


void Server::load_port( int argc, char ** argv ) {
    m_port = -1;
    for ( int i = 1 ; i < argc ; i++ ) {
	if ( argv[i] == "-P" ) {
	    if ( i != argc - 1 ) {
		m_port = atoi(argv[i+1]);
	    }
	}
    } 
    if ( m_port == -1 ) {
	m_port = 9999;
    }
}
