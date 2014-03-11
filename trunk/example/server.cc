#include <iostream>
#include "proto.hh"

using namespace std;

class session_on_server : public Serv_session {

public:

    session_on_server(int socket) : Serv_session(socket) {
	proto = new proto1(socket);
	proto->message["salut"]->sig_recv.connect(boost::bind(&session_on_server::salut, this, _1));
	proto->message["salut"]->operator()("1 2 3");
	(*proto)["ERR"]("c'est............... mal.... de..faire ca.. //end// ");

	(*proto)("IMG1")("djhfjdhfjk dhf jdhjhjhfjdh ", 5, 10 );
    }


    
    void salut(string msg) {
	stringstream ss(msg);
	int value;
	ss >> value;
	cout << "recu " << value << " ";
	ss >> value;
	cout << value << " ";
	ss >> value;
	cout << value << " " << endl;
    }




private:

};



int main(int argc, char ** argv) {
    Server<session_on_server> serv(argc, argv);
    serv.start();
    serv.join();
}
