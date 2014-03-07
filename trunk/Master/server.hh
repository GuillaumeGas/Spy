#ifndef _SESSION_MASTER_SERVER
#define _SESSION_MASTER_SERVER

#include <iostream>
#include "../Net.hh"
#include "proto.hh"


namespace master {

    Mutex m;

    class session_on_server : public Serv_session {
    public:
	session_on_server(int socket);
    
	void do_spy(std::string s);
	void do_dspy(std::string s);
	void do_control(std::string s);
	void do_observe(std::string s);

    
    
    };

};

#endif
