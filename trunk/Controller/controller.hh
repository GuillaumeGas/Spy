#ifndef _CONT
#define _CONT


#include "proto.hh"
#include "../Net.hh"
#include <iostream>
#include <map>


namespace controller {

    class controller_session : public Client_UDPSession {
    public:
    
	controller_session(int & write, int & read, std::string & ip);
	void do_YES(std::string);
	void on_begin();
	bool received();
	void send();
	std::pair < std::string, std::pair < std::string, int > > recv();
	void set_port(int);
	void set_ip(std::string);
	std::string info();
	
    private:
	bool m_recv;
	std::string m_info;
	std::string m_ip;
	int m_port;
	std::string name, ip;
	int port;
	
    };
};


#endif
