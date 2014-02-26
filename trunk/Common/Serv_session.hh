#ifndef _SERVSESSION
#define _SERVSESSION

#include "Thread.hh"
#include "Stream_net.hh"
#include <atomic>

class Serv_session : public Thread<Serv_session> {

public:

    Serv_session(int sock);
    void loop_recv();
    void session();
    void wait(std::string, Stream_net & s);
    ~Serv_session();

private:
    int m_sock;
    bool stop;
    std::map<std::string, std::string> message;
};



#endif
