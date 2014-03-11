#ifndef _SNIFFER
#define _SNIFFER

#include "proto.hh"
#include "../Master/client.hh"
#include "../Net.hh"
#include "controller.hh"
#include <iostream>
#include <map>

namespace controller {

    class Sniffer : public Thread < Sniffer > {

    public:

	Sniffer ( std::string mast_ip, int mast_port, int read , int write , int salle );
	void launch();
	void stop();
	void set_speed(int );
	void wait();

    private:

	std::string load_hostname();
	void send_to_master();
	void loop_recv( );
    
	Client_UDP < controller_session > snif_client;
	Client < master::master_cont > link_master;
	std::map < std::string , std::pair < std::string, int > > spy_map;

	int m_read, m_write, m_salle, m_speed;
	bool m_stop;
    };

};



#endif
