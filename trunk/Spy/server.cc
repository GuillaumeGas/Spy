#include "server.hh"

using namespace std;

namespace Spy {
    session_on_spy::session_on_spy(int socket) : Serv_session(socket) {
	auth = false;
	proto = new observer::proto_observer(socket);
	(*proto)["INFO"].sig_recv.connect(boost::bind(&session_on_spy::do_info, this, _1));
	(*proto)["WARNING"].sig_recv.connect(boost::bind(&session_on_spy::do_warning, this, _1));
	(*proto)["GET_LIST_PROC"].sig_recv.connect(boost::bind(&session_on_spy::do_get_list_proc, this, _1));
	(*proto)["GET_SCREENSHOT"].sig_recv.connect(boost::bind(&session_on_spy::do_get_screenshot, this, _1));
	(*proto)["GET_BIG_SCREENSHOT"].sig_recv.connect(boost::bind(&session_on_spy::do_get_big_screenshot, this, _1));
	(*proto)["SEND_CMD"].sig_recv.connect(boost::bind(&session_on_spy::do_send_cmd, this, _1));
	(*proto)["ADD_PROC"].sig_recv.connect(boost::bind(&session_on_spy::do_add_proc, this, _1));

	(*proto)["RETOUR"].sig_recv.connect(boost::bind ( &session_on_spy::do_retour, this, _1));

	begin.connect ( boost::bind ( &session_on_spy::on_begin, this));

	map_sessions.insert(pair<session_on_spy*, vector<string> >(this, vector<string>()));
    }

	
    void session_on_spy::on_begin() {
	m_content = rand()%20000;
	cout << m_content << endl;;
	unsigned long value  = expMod ( m_content, e, N );
	cout << expMod ( value, d, N) << endl;
	stringstream ss;
	ss << value;
	cout << value << endl;
	(*proto)["TEST"](ss.str());
    }

    void session_on_spy::do_retour ( string msg ) {
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

    void session_on_spy::do_info(string msg) {
	if ( auth ) {
	    MsgBox::info(msg);
	} else {
	    (*proto)["ERR"]("");
	    finish();
	}
    }

    void session_on_spy::do_warning(string msg) {
	if ( auth ) {
	    MsgBox::warning(msg);
	} else {
	    (*proto)["ERR"]("");
	    finish();
	}
    }
    
    void session_on_spy::do_get_list_proc(string) {
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
    
    void session_on_spy::do_get_screenshot(string data) {
	if ( auth ) {
	    stringstream s1, ss;
	    s1 << data;
	    double zoom;
	    s1 >> zoom;
		
	    ScreenShot sc(zoom);
	    int w, h;
	    //cout << "zoom : " << zoom << endl;
	    sc.save("test.bmp");
	    sc.get_stringstream("test.bmp", ss, w, h, zoom);
		
	    //cout << ss.str().length() << endl;
	    (*proto)("SCREENSHOT")(ss.str(), w, h);
	} else {
	    (*proto)["ERR"]("");
	    finish();
	}
    }

    void session_on_spy::do_get_big_screenshot(string data) {
	if ( auth ) {
	    
	    stringstream s1, ss;
	    s1 << data;
	    double zoom;
	    s1 >> zoom;
      
	    ScreenShot sc(zoom);
	    int w, h;
	    //cout << "zoom : " << zoom << endl;
	    sc.save("bigtest.bmp");
	    sc.get_stringstream("bigtest.bmp", ss, w, h, zoom);
		
	    //cout << ss.str().length() << endl;
	    (*proto)("BIG_SCREENSHOT")(ss.str(), w, h);
	} else {
	    (*proto)["ERR"]("");
	    finish();
	}
    }


    void session_on_spy::do_send_cmd(string _cmd) {
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

    void session_on_spy::do_add_proc(string proc) {
	map_sessions[this].push_back(proc.substr(0, proc.length()-1));
    }    





    void thread_spy_proc() {
	Process p;
	while(1) {
	    p.refresh();
	    for(auto it : map_sessions) {
		for(auto it2 : it.second) {
		    if(p.process_is_running(it2)) {
			stringstream ss;
			ss << p.get_proc_pid(it2);
			(*it.first->proto)["ALERT_PROC"](ss.str());
		    }
		}
	    }
	    sleep(1);
	}	
    }
};


    void init_cont_session (int read_port) {
	Client_UDP<controller::spy_session> client ( "localhost", read_port, read_port );
	char buffer[255];
	gethostname( buffer, 255 ); 
	client._session().set_ip(string(buffer));
	client._session().set_name( getlogin() );
	client._session().set_port( Spy::CURRENT_PORT );
	client._session().start();
	client.join();
    }





void load_file_args ( int &this_port, int &read_port,  string file_name) {
    ifstream file (file_name.c_str() );
    string aux;
    while ( !file.eof() ) {
	file >> aux;
	if ( aux == "spy_read_port=") {
	    file >> read_port;
	} else if ( aux == "spy_port=" ) {
	    file >> this_port;
	}
    }
    if ( this_port == -1 ) {
	this_port = 55555;
    }
    if ( read_port == -1 ) {
	read_port = 8888;
    }
    
}



string get_file_name(int argc, char ** argv) {
    for (int i = 0 ; i < argc - 1 ; i++) {
	if ( strcmp ( argv[i], "-f" ) == 0) {
	    return argv[i+1];
	}
    }
    return "../def.conf";
}



int main(int argc, char** argv) {
    boost::thread th(Spy::thread_spy_proc);
    th.detach();

    int this_port = -1, read_port = -1;
    load_file_args( this_port, read_port, get_file_name(argc, argv));
    
    srand(time(NULL));
    Server <Spy::session_on_spy> serv(this_port);
    Spy::CURRENT_PORT = serv._port();
    thread t(init_cont_session, read_port);
    serv.start();
    serv.join();
}
