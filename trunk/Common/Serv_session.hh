#ifndef _SERVSESSION
#define _SERVSESSION

#include "Thread.hh"
#include "Stream_net.hh"
#include <atomic>
#include <sstream>
#include <boost/signals2.hpp>

using boost::signals2::signal;

class Message;


class Serv_session : public Thread<Serv_session> {

public:

    Serv_session(int sock);
    void loop_recv();
    void session();
    void send_msg(Message &s, std::string);
    std::string wait(Message &s);
    ~Serv_session();

protected:
    int m_sock;
    bool stop;
    Stream_net my_stream;
    /*    std::map<std::string, std::string> message;
    std::map<std::string, signal<void(std::string)>* > sig_msg;
    std::map<std::string, signal<void(std::string, std::string)>* > sig_send;*/
    std::map < std::string, Message* > message;
};



#endif
