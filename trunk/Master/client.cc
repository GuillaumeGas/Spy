#include "client.hh"
#include <sstream>

using namespace std;



int main(int argc, char ** argv) {
    Client< master::master_obse > cli(argc, argv);
    cli._session().send("27");
    
    while ( !cli._session().received() ) {
    }
    for ( auto it : cli._session().get_map() ) {
	cout << it.first << " " << it.second.first << " " << it.second.second << endl;
    }
    cli.join();
}
