#ifndef _SERVSESSION
#define _SERVSESSION

#include "Thread.hh"
class Serv_session : public Thread<Serv_session> {

public:

    Serv_session(int sock);
    void loop_recv();
    void session();
    ~Serv_session();

private:
    int m_sock;
    bool stop;
};



#endif
