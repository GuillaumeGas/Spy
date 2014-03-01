#ifndef _PROTO
#define _PROTO

#include "../Common/protocol.hh"
#include "../Common/Message.hh"

class proto1 : public Protocol {
public:

    proto1(int socket) : Protocol(socket) {
	message["salut"] = new Message("salut", "1s3i", this);
	message["ERR"] = new Message("ERR", "1s1a", this);
    }
    
    
};

#endif
