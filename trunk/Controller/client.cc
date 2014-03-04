#include "client.hh"
#include "../Master/client.hh"
#include "proto.hh"

using namespace std;

namespace controller {


    controller_master::controller_master(){
	Client <master::master_cont> cli("localhost", 9999);
	cli.join();
	map < string, pair < string, int > > s = cli._session().get_map();
	m_stop = false;
	for ( auto it : s ) {
	    cout << it.first << endl;
	    int port = it.second.second;
	    string ip = it.second.first;
	    spy[it.first] = new Client < controller_client >(ip, port);
	}
	loop_cmd();
    }



    void controller_master::loop_cmd() {
	while ( ! m_stop ) {
	    /* interface graphique */
	    string name;
	    cout << "nom ?" << endl;
	    cin >> name;
	    auto it = spy.find(name);
	    if ( it  != spy.end() ) {
		string cmd;
		stringstream ss;
		cout << "cmd ?" << endl;
		cin.clear();
		getline(cin, cmd);
		ss << cmd << " //end//";
		it->second->_session().proto->message["CMD"]->operator()(ss.str());
	    } else {
		cout << " Inconnu desole " <<endl;
	    }
	}
    }


    controller_client::controller_client( int socket ): Client_session(socket) {
	proto = new cont_proto(socket);
	(*proto)["RETURN"].sig_recv.connect(boost::bind(&controller_client::do_return , this, _1));
    }

    void controller_client::do_return(string msg) {
	cout << msg << endl;
    }
    
};


int main(int argc, char ** argv) {
    controller::controller_master m;
}
