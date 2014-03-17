#ifndef _CLIENT_OBS
#define _CLIENT_OBS

#include <iostream>

#include "../Net.hh"
#include "proto.hh"
#include "../Spy/ScreenShot.hh"
#include "../Master/client.hh"
#include <boost/signals2.hpp>

using boost::signals2::signal;

namespace observer {
    class session_on_observer : public Client_session {
    public:
	session_on_observer(int socket);

	void info(std::string msg);
	void do_list_proc(std::string data);
	void do_screenshot(std::string data, int w, int h);
	void do_big_screenshot(std::string data, int w, int h);
	void do_res_cmd(std::string data);

	void set_name(std::string);

	signal<void(std::string, std::string)> img_recv;
	signal<void(std::string)>              big_img_recv;

    private:
	std::string m_name;

	Mutex mutex;

    };
};

#endif
