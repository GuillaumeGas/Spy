#ifndef _PROTOUDP
#define _PROTOUDP

#include "../Common/UDP_protocol.hh"
#include "../Common/UDP_Message.hh"
#include <iostream>

class udp_proto : public UDP_Protocol {
public:

    udp_proto ( int & port , int & port2, std::string & ip ) : UDP_Protocol ( port, port2, ip ) {
	message["salut"] = new UDP_Message("salut", "1s", this);
	message["bonjour"] = new UDP_Message("bonjour", "1s1s", this);
    }

};


#endif
