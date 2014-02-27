#ifndef _SESSION_MASTER_CLIENT
#define _SESSION_MASTER_CLIENT

#include <iostream>
#include "../Common/Client.hh"
#include "../Common/Client_session.hh"
#include "../Common/Message.hh"
#include "proto.hh"

namespace master {

    class session_on_client : public Client_session {
    public:	
	session_on_client( int socket );
	
	void do_ok(std::string msg);
	void do_err(std::string msg);
	void do_spy(std::string msg);

    };

};




#endif
