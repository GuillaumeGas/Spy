#ifndef _PROTO_SPY
#define _PROTO_SPY

#include "../Common/protocol.hh"
#include "../Common/Message.hh"

class spy_proto : public Protocol {
public:
    spy_proto(int socket) : Protocol(socket) {
        
    }
};

#endif