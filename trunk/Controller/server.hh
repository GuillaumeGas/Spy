#ifndef _CONTSERV
#define _CONTSERV


#include <iostream>
#include "../Spy/Cmd.hh"
#include "../Common/Server.hh"
#include "../Common/Serv_session.hh"

namespace controller {

    class controller_server : public Serv_session {
    public:

	controller_server(int);

	void do_ok(std::string);
	void do_err(std::string);
	void do_cmd(std::string);

    private:
	
    };

};





#endif
