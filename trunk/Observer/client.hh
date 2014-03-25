#ifndef _CLIENT_OBS
#define _CLIENT_OBS

#include <iostream>

#include <QMap>
#include <QString>

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

	void do_test(std::string s);
	void do_ok(std::string s);
	void do_err(std::string s);

	void do_alert_proc(std::string);

	void set_name(std::string);

	int get_pid_detected();//renvoie le pid du dernier processus surveillé détecté
	std::string get_proc_detected(); //renvoie le nom du dernier processus surveillé détecté
	void set_pid_detected(int);

	signal<void(std::string, std::string)> img_recv;
	//signal<void(std::string)>              big_img_recv;
	signal<void(std::string)>              proc_recv;
	signal<void(QString, std::string)> lst_proc_recv;
	signal<void(std::string, std::string)>    res_cmd_recv;

    private:
	std::string m_name;
	unsigned long N, e;
	Mutex mutex;
	unsigned long m_d;
	
	int last_pid_detected;
	std::string last_proc_detected;
    };
};

#endif
