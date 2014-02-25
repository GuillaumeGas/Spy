#include "Server.hh"
#include "Serv_session.hh"

int main(int argc, char ** argv) {
    Server<Serv_session> s(argc, argv);
    s.start();
}
