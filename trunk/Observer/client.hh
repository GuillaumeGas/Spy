#ifndef _CLIENT_OBS
#define _CLIENT_OBS

#include <iostream>

#include "../Net.hh"
#include "proto.hh"
#include "../Spy/ScreenShot.hh"
#include "../Master/client.hh"
#include <boost/signals2.hpp>

using namespace std;
using boost::signals2::signal;

namespace observer {
    class session_on_observer : public Client_session {
    public:
	session_on_observer(int socket);

	void info(string msg);
	void do_list_proc(string data);
	void do_screenshot(string data, int w, int h);    
	void do_res_cmd(string data);

	void set_name(std::string);

	signal<void(std::string, std::string)> img_recv;

    private:
	std::string m_name;

    };
};

#endif
