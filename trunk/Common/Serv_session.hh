#ifndef _SERVSESSION
#define _SERVSESSION

#include "Thread.hh"
#include "Session.hh"
#include <atomic>
#include <sstream>
#include <boost/signals2.hpp>

using boost::signals2::signal;

class Message;


class Serv_session : public Thread<Serv_session>, public Session {

public:

    Serv_session(int sock);
    void loop_recv();
    void session();

    ~Serv_session();

protected:

    bool stop;

    /*    std::map<std::string, std::string> message;
    std::map<std::string, signal<void(std::string)>* > sig_msg;
    std::map<std::string, signal<void(std::string, std::string)>* > sig_send;*/

};



#endif
