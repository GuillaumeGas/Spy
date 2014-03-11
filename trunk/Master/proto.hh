#ifndef _PROTO
#define _PROTO

#include "../Net.hh"

class master_proto : public Protocol {
    
public:
    
    master_proto ( int socket ) : Protocol ( socket ) {
	
	message["OBSERVE"] = new Message("OBSERVER", "1s1i", this);
	message["OK"] = new Message("OK", "1s", this);
	message["ERR"] = new Message("ERR", "1s", this);
	message["MAP_SPY"] = new Message("MAP_SPY", "1s1i1a", this);
    }
    
};





#endif
