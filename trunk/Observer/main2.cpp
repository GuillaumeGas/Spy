#include "client.hh"
#include "../Net.hh"

int main(int argc, char ** argv) {
    Client < observer::session_on_observer > client (argc, argv);
    client.join();
}
