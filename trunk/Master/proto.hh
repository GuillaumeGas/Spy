#ifndef _PROTO
#define _PROTO

#include "../Net.hh"

class master_proto : public Protocol {
    
public:
    
    master_proto ( int socket ) : Protocol ( socket ) {
	message["SPY"] = new Message("SPY", "1s2s1i", this); //prend le nom du poste l'adresse et le port
	message["CONTROL"] = new Message("CONTROL", "1s", this);
	message["OBSERVE"] = new Message("OBSERVER", "1s", this);
	message["OK"] = new Message("OK", "1s", this);
	message["ERR"] = new Message("ERR", "1s", this);
	message["DSPY"] = new Message("DSPY", "1s1s", this);
    }
    
};





#endif
