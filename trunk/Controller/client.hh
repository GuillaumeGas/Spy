#ifndef _CONTROLLER
#define _CONTROLLER

#include "../Common/Client.hh"
#include "../Common/Client_session.hh"
#include "../Common/Message.hh"
#include <iostream>

namespace controller {

    class controller_client : public Client_session {
    public:
	
	controller_client(int);
	
	void do_return(std::string);
	

    private:
	std::string name;
	std::string ip;
	int port;
	
    };


    class controller_master {
    public:

	controller_master();
	void loop_cmd();

    private:

	std::map <std::string, Client < controller_client >* > spy;
	bool m_stop;


    };





};



#endif
