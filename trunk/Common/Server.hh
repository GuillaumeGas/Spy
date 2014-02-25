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

class Server {

public:

    Server(int argc, char ** argv);
    void start();

private:
    
    void load_port(int argc, char ** argv);
    void init_sock();
    void init_addr();
    void do_accept();
    void do_bind();
    void do_listen();
    void loop_accept();
    std::vector<Serv_session> multi_thread;
    int m_port, m_sock;
    sockaddr_in sin;
};


#endif

