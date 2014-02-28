#ifndef _CLIENT_SESSION
#define _CLIENT_SESSION

#include <map>
#include <iostream>
#include <boost/signals2.hpp>
#include "Thread.hh"
#include "Stream_net.hh"

#include "protocol.hh"

using boost::signals2::signal;

class Message;


class Client_session : public Thread<Client_session>{
public:
    Client_session(int _sock);
  
    void loop_recv();
  
    int get_sock()const;
    bool IsStopped()const;

    void set_stop();

protected:
    signal<void()> begin;
    signal<void()> end;
    int m_sock;
    bool m_stop;
    Protocol * proto;
};

#endif
