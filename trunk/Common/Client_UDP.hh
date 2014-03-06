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

    Client_UDP ( string ip, int port) {
	
    }
    
    Client_UDP ( int argc, char * argv) {
	load_portIp(argc, argv);
    }

private:


    void init_info() {
	m_sock = socket( AF_INET, SOCK_DGRAM, 0 );
	m_sin = {0};
	m_sin.sin_addr.s_addr = htonl(INADDR_ANY);
	m_sin.sin_family = AF_INET;
	m_sin.sin_port = htons(m_port);
	hostent * hostinfo = NULL;
	hostinfo = gethostbyname(m_ip.c_str());
	m_sin.sin_addr = *(in_addr*)hostinfo->h_addr; 
	T = new T(m_sin);
    }


    void load_portIp(int argc, char ** argv) {
	m_port = -1;
	m_ip = "";
	for ( int i = 1 ; i < argc - 1 ; i++ ) {
	    if ( strcmp(argv[i], "-P") == 0 ) {
		m_port = atoi(argv[i+1]);
	    } else if ( strcmp( argv[i], "-H" ) == 0 ) {
		m_ip = argv[i + 1];
	    }
	}
	if ( m_port == -1 ) {
	    m_port = 9999;
	} 
	if ( m_ip == "" ) {
	    m_ip = localhost;
	}
    }


    string m_ip;
    int m_port, m_socket;
    sockaddr_in m_sin;
    T * session;
};


#endif
