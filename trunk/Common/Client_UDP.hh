#ifndef _CLIE_UDP
#define _CLIE_UDP


#include <iostream>
#include <vector>
#include <cerrno>
#include <cstdio>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

template <typename T>
class Client_UDP {
public:

    Client_UDP ( std::string ip, int port) {	
    }
    
    Client_UDP ( int argc, char **argv) {
	load_portIp(argc, argv);
	init_info();
    }


    void join() {
	session->join();
    }

    T & _session() {
	return * session;
    }

private:


    void init_info() {
	session = new T(m_port, m_port2, m_ip);
    }


    void load_portIp(int argc, char ** argv) {
	m_port = -1;
	m_ip = "";
	for ( int i = 1 ; i < argc - 1 ; i++ ) {
	    if ( strcmp(argv[i], "-R") == 0 ) {
		m_port = atoi(argv[i+1]);
	    } else if ( strcmp( argv[i], "-H" ) == 0 ) {
		m_ip = argv[i + 1];
	    } else if ( strcmp(argv[i], "-W") == 0 ) {
		m_port2 = atoi(argv[i+1]);
	    }
	}
	if ( m_port == -1 ) {
	    m_port = 9999;
	} 
	if ( m_port2 == -1 ) {
	    m_port2 = 9998;
	}
	if ( m_ip == "" ) {
	    m_ip = "localhost";
	}
    }


    std::string m_ip;
    int m_port, m_sock, m_sensock, m_port2;
    sockaddr_in m_sin;
    T * session;
};


#endif
