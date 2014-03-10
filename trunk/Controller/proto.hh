#ifndef _CONTPROTO
#define _CONTPROTO

#include "../Net.hh"
#include <iostream>


class cont_proto : public UDP_Protocol {

public:

    cont_proto ( int & write , int & read, std::string & ip ) : UDP_Protocol ( write, read, ip) {
	message["HERE?"] = new UDP_Message("HERE?", "1s1s1i", this);
	message["YES"] = new UDP_Message("YES", "1s1s1s1i", this);
    }



};




#endif
