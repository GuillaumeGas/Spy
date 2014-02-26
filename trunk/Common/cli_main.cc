#include "Client.hh"
#include "Client_session.hh"

int main(int argc, char** argv) {

  Client<Client_session> cli(argc, argv);

  return 0;
}
