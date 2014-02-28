#include "client.hh"
#include <sstream>

using namespace std;



int main(int argc, char ** argv) {
    Client< master::master_spy_co > cli(argc, argv);
    cli._session().name() = "jacque";
    cli._session().addr() = "localhost";
    cli._session().port() = 9999;
    cli._session().isset() = true;
    cli.join();
    Client< master::master_cont > client(argc, argv);
    client.join();
}
