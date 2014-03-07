#ifndef _SERVSESSION
#define _SERVSESSION

#include "Thread.hh"

#include <atomic>
#include <sstream>
#include <boost/signals2.hpp>
#include "protocol.hh"

using boost::signals2::signal;

class Message;


class Serv_session : public Thread<Serv_session> {

public:

    Serv_session(int sock);
    void loop_recv();
    void session();

    ~Serv_session();

protected:
    signal<void()> begin;
    signal<void()> end;
    bool stop;
    Protocol * proto;

};



#endif
