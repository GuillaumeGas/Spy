#ifndef _CLIENT_SESSION
#define _CLIENT_SESSION

#include <map>
#include <iostream>

#include "Thread.hh"
#include "Stream_net.hh"

#include "protocol.hh"

class Message;


class Client_session : public Thread<Client_session>{
public:
    Client_session(int _sock);
  
    void loop_recv();
  
    int get_sock()const;
    bool IsStopped()const;

    void set_stop();

protected:
    int m_sock;
    bool m_stop;
    Protocol * proto;
};

#endif
