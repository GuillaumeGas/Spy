#ifndef _SPY_CONT
#define _SPY_CONT


#include "proto.hh"
#include "../Common/Client_UDP.hh"
#include "../Common/Client_UDPSession.hh"
#include <iostream>

namespace controller {

    class spy_session : public Client_UDPSession {
    public:

	spy_session ( int & , int & , std::string & );
	void do_HERE(std::string);

    };

};




#endif
