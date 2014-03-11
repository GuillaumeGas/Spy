#include <iostream>
#include <sstream>
#include <map>

#include "proto.hh"
#include "../Net.hh"

using namespace std;

namespace Observer {
  class session_on_observer : public Client_session {
  public:
    session_on_observer(int socket) : Client_session(socket) {
      proto = new proto_observer(socket);
      (*proto)["info"].sig_recv.connect(boost::bind(&session_on_observer::info, this, _1));
      (*proto)["list_proc"].sig_recv.connect(boost::bind(&session_on_observer::do_list_proc, this, _1));

      //(*proto)["info"]("Le message //end//");
      //(*proto)["warning"]("err !! //end//");
      (*proto)["get_list_proc"]("");
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
  };
};

int main(int argc, char** argv) {
  Client <Observer::session_on_observer> client(argc, argv);
  client.join();
}
