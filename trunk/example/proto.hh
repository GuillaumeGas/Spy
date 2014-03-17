#ifndef _PROTO
#define _PROTO

#include "../Net.hh"
#include <iostream>
using namespace std;

int N = 1387;
int e = 1255;



int expMod ( long value, long exp, int mod ) {
    if ( exp == 0 ) {
	return 1;
    } else {
	int q = exp/2;
	int r = exp%2;
	int a2 = expMod(value, q, mod )%mod;
	if ( r == 1 ) {
	    return (a2 * a2) %mod  * value % mod;
	} else {
	    return (a2 * a2) % mod;
	}
    }
}


enum State_t {
    begin,
    auth
};



class proto1 : public Protocol {
public:

    proto1(int socket) : Protocol(socket) {
	message["TEST"] = new Message("TEST", "1s1i", this);
	message["RETOUR"] = new Message("RETOUR", "1s1i", this);
	message["OK"] = new Message("OK", "1s", this);
	message["ERR"] = new Message("ERR", "1s", this);
	message["salut"] = new Message("salut", "1s", this);
    }
    
    
};

#endif
