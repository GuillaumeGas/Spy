#include "client.hh"
#include <sstream>

using namespace std;

namespace master {

    session_on_client::session_on_client ( int socket ) : Client_session(socket) {
	proto = new master_proto(socket);
	start();
	proto->message["OK"]->sig_recv.connect(boost::bind(&session_on_client::do_ok, this, _1));
	proto->message["ERR"]->sig_recv.connect(boost::bind(&session_on_client::do_err, this, _1));
	proto->message["SPY"]->sig_recv.connect(boost::bind(&session_on_client::do_spy, this, _1));
	proto->message["CONTROL"]->operator()("");
	while ( !m_stop ) {	
	
	}
	proto->message["SPY"]->operator()("norbert localhost 9999");
    }


    void session_on_client::do_ok(string msg) {
	cout << "[SYS] -> OK" << endl;
	m_stop = true;
    }

    void session_on_client::do_err(string msg) {
	cout << "[SYS] -> ERR" << endl;
    }


    void session_on_client::do_spy(string msg) {
	stringstream ss(msg);
	int port;
	string addr, name;
	ss >> name >> addr >> port;
	cout << name << " " << addr << " " << port << endl;
    }


};


int main(int argc, char ** argv) {
    Client< master::session_on_client> client(argc, argv);
}
