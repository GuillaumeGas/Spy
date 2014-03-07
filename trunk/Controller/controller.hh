#ifndef _CONT
#define _CONT


#include "proto.hh"
#include "../Common/Client_UDP.hh"
#include "../Common/Client_UDPSession.hh"
#include <iostream>


namespace controller {

    class controller_session : public Client_UDPSession {
    public:
    
	controller_session(int & write, int & read, std::string & ip);
	void do_YES(std::string);
	void on_begin();
	bool received();
	std::string info();
	
    private:
	bool m_recv;
	std::string m_info;
  
    };
};


#endif
