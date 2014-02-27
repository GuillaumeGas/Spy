#ifndef _CLIENT_SESSION
#define _CLIENT_SESSION

#include <map>
#include <iostream>

#include "Thread.hh"
#include "Stream_net.hh"

class Message;


class Client_session : Thread<Client_session>{
public:
    Client_session(int _sock);
  
    void loop_recv();
  
    int get_sock()const;
    bool IsStopped()const;

    void set_stop();

private:
    int m_sock;
    bool m_stop;
    std::map<std::string, Message<Client_session> *> message;
};

#endif
