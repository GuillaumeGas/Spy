#include <iostream>

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
      (*proto)["info"].sig_recv.connect(boost::bind(&session_on_spy::info, this, _1));
      (*proto)["warning"].sig_recv.connect(boost::bind(&session_on_spy::warning, this, _1));
      
    }

    void info(string msg) {
      MsgBox::info(msg);
    }

    void warning(string msg) {
      MsgBox::warning(msg);
    }

    
  };
};

int main(int argc, char** argv) {
  Server <Spy::session_on_spy> serv(argc, argv);
  serv.start();
  serv.join();
}
