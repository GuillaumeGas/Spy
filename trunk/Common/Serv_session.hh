#ifndef _SERVSESSION
#define _SERVSESSION

#include "Thread.hh"
class Serv_session : public Thread<Serv_session> {

public:

    Serv_session(int sock);
    void session();
    ~Serv_session();

private:
    int m_sock;
};



#endif
