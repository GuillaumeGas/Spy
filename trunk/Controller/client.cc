#include "client.hh"
#include "../Master/client.hh"
#include "proto.hh"

using namespace std;

namespace controller {


    controller_master::controller_master(){
	Client <master::master_cont> cli("localhost", 9999);
	cli.join();
	spy = cli._session().get_map();
	for ( auto it : spy ) {
	    cout << it.first << " " << it.second.first << " " << it.second.second << endl;
	}
    }


    controller_client::controller_client( int socket ): Client_session(socket) {
	proto = new cont_proto(socket);
	(*proto)["RETURN"].sig_recv.connect(boost::bind(&controller_client::do_return , this, _1));

	string cmd;
	stringstream ss;
	cout << "cmd :";
	cin >> cmd;
	ss << cmd <<  " //end//";
	(*proto)["CMD"](ss.str());
    }

    void controller_client::do_return(string msg) {
	cout << msg << endl;
    }
    
};


int main(int argc, char ** argv) {
    Client < controller::controller_client > client(argc, argv);
    client.join();
}
