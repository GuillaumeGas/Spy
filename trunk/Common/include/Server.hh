#ifndef _SERVER
#define _SERVER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <pthread.h>

#include "Thread.hh"
#include "Serv_session.hh"
#include <vector>
#include <boost/signals2.hpp>

using boost::signals2::signal;

template <typename T>
class Server : public Thread < Server<T> >{

public:

    Server(int argc, char ** argv) : Thread < Server<T> >(&Server::loop_accept, this){
	load_port(argc, argv);
	init_sock();
	init_addr();
	do_bind();
	do_listen();
	m_stop = false;
    }
    

    void loop_accept() {
	socklen_t size_addr = sizeof(sin);
	started();
	while ( !m_stop ) {
	    int client = accept( m_sock, (sockaddr *)&sin, &size_addr);
	    if ( client != - 1 ) {
		std::cout << "[INFO] -> new client " << std::endl;
		multi_thread.push_back(new T(client));
		multi_thread[multi_thread.size() - 1]->start();
	    } else {
		continue;
	    }
	}

    }


    int & _port() {
	return m_port;
    }



    void finish() {
	this->kill();
	stoped();
    }


    signal<void()> started;
    signal<void()> stoped;



private:
    
    void load_port(int argc, char ** argv) {
	m_port = -1;
	for ( int i = 1 ; i < argc ; i++ ) {
	    if ( strcmp(argv[i], "-P") == 0 ) {
		if ( i != argc - 1 ) {
		    m_port = atoi(argv[i+1]);
		}
	    }
	} 
	if ( m_port == -1 ) {
	    m_port = 9999;
	}
    }

    void init_sock() {    
	m_sock = socket(AF_INET, SOCK_STREAM, 0);
    }

    void init_addr() {
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(m_port);
    }




    void do_bind() {
	if ( bind( m_sock, (sockaddr *) &sin, sizeof(sin)) == -1 ) {
	    std::cout << "Probleme de bind changer de Port" << std::endl;
	    throw m_port;
	} else {
	    std::cout << "[INFO] -> bind success " << std::endl;
	}
    }

    void do_listen() {
	if ( listen( m_sock, 0 ) == -1 ) {
	    std::cout << "Probleme de listen changer de Pc" << std::endl;
	    throw m_sock;
	} else {
	    std::cout << "[INFO] -> listen success" << std::endl;
	}
    }



    std::vector<T*> multi_thread;
    int m_port, m_sock;
    sockaddr_in sin;
    bool m_stop;
};


#endif

