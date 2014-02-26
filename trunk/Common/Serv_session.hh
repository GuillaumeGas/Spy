#ifndef _SERVSESSION
#define _SERVSESSION

#include "Thread.hh"
#include "Stream_net.hh"
#include <atomic>
#include <sstream>
#include <boost/signals2.hpp>

using boost::signals2::signal;

class Serv_session : public Thread<Serv_session> {

public:

    Serv_session(int sock);
    void loop_recv();
    void session();
    std::string wait(std::string, Stream_net & s);
    ~Serv_session();

private:
    int m_sock;
    bool stop;
    std::map<std::string, std::string> message;
    std::map<std::string, signal<void(std::string)>* > sig_msg;
};



#endif
