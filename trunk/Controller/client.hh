#ifndef _CONTROLLER
#define _CONTROLLER

#include "../Common/Client.hh"
#include "../Common/Client_session.hh"
#include "../Common/Message.hh"
#include <iostream>

namespace controller {

    class controller_session {
    public:

	controller_session(  );

    private:

	std::map <std::string, std::pair<std::string, int> > spy;
    


    };
};



#endif
