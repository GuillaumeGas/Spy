#include "Server.hh"
#include "Serv_session.hh"
#include "Stream_net.hh"



int main(int argc, char ** argv) {
    Server<Serv_session> server(argc, argv);
    server.start();
}
