#ifndef _CONTROLLER
#define _CONTROLLER

#include "../Common/Client.hh"
#include "../Common/Client_session.hh"
#include "../Common/Message.hh"
#include <iostream>

namespace controller {

    class controller_master {
    public:

	controller_master();

    private:

	std::map <std::string, std::pair<std::string, int> > spy;
    


    };




    class controller_client : public Client_session {
    public:
	
	controller_client(int);
	
	void do_return(std::string);
	

    private:
	std::string name;
	std::string ip;
	int port;
	
    };

};



#endif
