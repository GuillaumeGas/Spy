#include "client.hh"
#include "../Master/client.hh"
using namespace std;

namespace controller {


    controller_session::controller_session(){
	Client <master::master_cont> cli("localhost", 9999);
	cli.join();
	spy = cli._session().get_map();
	for ( auto it : spy ) {
	    cout << it.first << " " << it.second.first << " " << it.second.second << endl;
	}
    }

};


int main(int argc, char ** argv) {
    controller::controller_session cont;
}
