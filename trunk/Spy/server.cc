#include <iostream>
#include <sstream>
#include <map>

#include "proto.hh"
#include "../Net.hh"
#include "MsgBox.hh"
#include "Process.hh"

using namespace std;

namespace Spy {
  class session_on_spy : public Serv_session {
  public:
    session_on_spy(int socket) : Serv_session(socket) {
      proto = new proto_observer(socket);
      (*proto)["info"].sig_recv.connect(boost::bind(&session_on_spy::do_info, this, _1));
      (*proto)["warning"].sig_recv.connect(boost::bind(&session_on_spy::do_warning, this, _1));
      (*proto)["get_list_proc"].sig_recv.connect(boost::bind(&session_on_spy::do_get_list_proc, this, _1));
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
  };
};

int main(int argc, char** argv) {
  Server <Spy::session_on_spy> serv(argc, argv);
  serv.start();
  serv.join();
}
