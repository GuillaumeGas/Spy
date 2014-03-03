#ifndef _PROTOCONT
#define _PROTOCONT


#include "../Common/protocol.hh"
#include "../Common/Message.hh"


namespace controller {

    class cont_proto : public Protocol {
    public:
	cont_proto( int socket ) : Protocol (socket) {
	    message["CMD"] = new Message("CMD", "1s1a", this);
	    message["RETURN"] = new Message("RETURN", "1s1a", this);
	    message["ERR"] = new Message("ERR", "1s1a", this);
	    message["OK"] = new Message("OK", "1s", this);
	}
    };

};



#endif
