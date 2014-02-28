#include "client.hh"
#include <sstream>

using namespace std;

namespace master {

    master_spy_co::master_spy_co ( int socket ) : Client_session( socket ) {
	proto = new master_proto(socket);
	(*proto)["OK"].sig_recv.connect(boost::bind(&master_spy_co::do_ok, this, _1));
	begin.connect(boost::bind(&master_spy_co::do_begin, this));
	start();
	while( !m_stop ){}
    }

    void master_spy_co::do_begin() {
	(*proto)["SPY"]("norbert localhost 9999");
    }


    void master_spy_co::do_ok ( string msg ) {
	cout << "[SYS] -> OK " << endl;
	m_stop = true;
    }
    

};


int main(int argc, char ** argv) {
    Client< master::master_spy_co > client(argc, argv);
}
