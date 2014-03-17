#include "client.hh"

using namespace std;

namespace observer {
    session_on_observer::session_on_observer(int socket) : Client_session(socket) {
	proto = new observer::proto_observer(socket);
	(*proto)["INFO"].sig_recv.connect(boost::bind(&session_on_observer::info, this, _1));
	(*proto)["LIST_PROC"].sig_recv.connect(boost::bind(&session_on_observer::do_list_proc, this, _1));
	(*proto)["RES_CMD"].sig_recv.connect(boost::bind(&session_on_observer::do_res_cmd, this, _1));
	(*proto)("SCREENSHOT").sig_recv.connect(boost::bind(&session_on_observer::do_screenshot, this, _1, _2, _3));
	(*proto)("BIG_SCREENSHOT").sig_recv.connect(boost::bind(&session_on_observer::do_big_screenshot, this, _1, _2, _3));

	//(*proto)["info"]("Le message //end//");
	//(*proto)["warning"]("err !! //end//");
	//(*proto)["get_list_proc"]("");
	//(*proto)["get_screenshot"]("0.5");
	//(*proto)["send_cmd"]("ls //end//");
    }

    void session_on_observer::info(string msg) {
	cout << "msg : " << msg << endl;
    }

    void session_on_observer::do_list_proc(string data) {
	cout << "reception processus actifs" << endl;
	int size;
	stringstream ss(data);
      
	map<int, string> list;
	while(!ss.eof()) {
	    int pid;
	    string tmp;
	    ss >> pid;
	    ss >> tmp;
	    list[pid] = tmp;
	
	    cout << pid << " " << list[pid] << endl;
	}
    }

    void session_on_observer::do_screenshot(string data, int w, int h) {
	cout << "Telechargement..." << endl;

	data = data.substr( 1 , data.length()-1 );
	stringstream ss(data);

	string file_name = m_name;
	file_name += ".bmp";
	
	mutex.lock();
	ScreenShot::build_bmp_fromStringstream(file_name.c_str(), ss, w, h);
	mutex.unlock();

	cout << "Image telechargee !!" << endl;

	img_recv(m_name, file_name.c_str());
    }

    void session_on_observer::do_big_screenshot(string data, int w, int h) {
	cout << "Telechargement bigImg..." << endl;

	data = data.substr( 1 , data.length()-1 );
	stringstream ss(data);

	string file_name = m_name;
	file_name += "_big.bmp";
	
	mutex.lock();
	ScreenShot::build_bmp_fromStringstream(file_name.c_str(), ss, w, h);
	mutex.unlock();

	cout << "Image telechargee !!" << endl;

	big_img_recv(file_name.c_str());
    }
    
    void session_on_observer::do_res_cmd(string data) {
	cout << data << endl;
    }

    void session_on_observer::set_name(string name) {
	m_name = name;
    }
};
