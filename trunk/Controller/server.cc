#include "server.hh"
#include "proto.hh"
#include "../Master/client.hh"

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
	cout << ss.str() << endl;
	(*proto)["RETURN"](ss.str());
    }

};




void serv_start() {
    Client < master::master_spy_co > cli_co("localhost", 9999);
    cli_co._session().name() = "emile";
    cli_co._session().addr() = "localhost";
    cli_co._session().port() = 8888;
    cli_co._session().isset() = true;
    cli_co.join();
}



void serv_stop() {
    Client < master::master_spy_deco > cli_deco("localhost", 9999);
    cli_deco._session().name() = "emile";
    cli_deco._session().isset() = true;
    cli_deco.join();
}


int main( int argc, char ** argv ) {

    Server< controller::controller_server > serv(argc, argv);
    serv.started.connect(serv_start);
    serv.stoped.connect(serv_stop);
    serv.start();
    serv.join();
    serv.finish();
}
