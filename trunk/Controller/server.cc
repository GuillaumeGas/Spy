#include "server.hh"
#include "proto.hh"

using namespace std;

namespace controller {

    controller_server::controller_server ( int socket ) : Serv_session( socket ) {
	proto = new cont_proto(socket);
	(*proto)["CMD"].sig_recv.connect(boost::bind(&controller_server::do_cmd, this, _1));
	(*proto)["OK"].sig_recv.connect(boost::bind(&controller_server::do_ok, this, _1));
	(*proto)["ERR"].sig_recv.connect(boost::bind(&controller_server::do_err, this, _1));
    }


    void controller_server::do_ok( string msg ) {
	cout << "[SYS] -> OK" << endl;
    }

    void controller_server::do_err( string msg ) {
	cout << "[SYS] -> ERR " << msg << endl;
    }

    void controller_server::do_cmd( string cmd ) {
	Cmd::exec(cmd.c_str());
	stringstream ss;
	ss << Cmd::get_res() << " //end//";

	(*proto)["RETURN"](ss.str());
    }

};


int main( int argc, char ** argv ) {
    Server< controller::controller_server > serv(argc, argv);
    serv.start();

}
