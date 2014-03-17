#ifndef _PROTO
#define _PROTO

#include "../Net.hh"


int N = 75044909;
int e = 5342377;


unsigned long expMod ( unsigned long value, unsigned long exp, int mod ) {
    if ( exp == 0 ) {
	return 1;
    } else {
	int q = exp/2;
	int r = exp%2;
	unsigned long a2 = expMod(value, q, mod )%mod;
	if ( r == 1 ) {
	    return (a2 * a2) %mod  * value % mod;
	} else {
	    return (a2 * a2) % mod;
	}
    }
}


namespace observer {
    class proto_observer : public Protocol {
    public:
	proto_observer(int socket) : Protocol(socket) {
	    message["INFO"]          = new Message("INFO", "1s1a", this);
	    message["WARNING"]       = new Message("WARNING", "1s1a", this);
	    message["GET_LIST_PROC"] = new Message("GET_LIST_PROC", "1s", this); //demande la liste de processu actifs
	    message["LIST_PROC"]     = new Message("LIST_PROC", "1s1a", this); //réponse : liste processus actifs
	    /* a debug */
	    message["GET_SCREENSHOT"]= new Message("GET_SCREENSHOT", "1s1s", this); //demande un screenshot (param : zoom)
	    message["GET_BIG_SCREENSHOT"] = new Message("GET_BIG_SCREENSHOT", "1s1s", this);
	    imessage["SCREENSHOT"]    = new Img_Message("SCREENSHOT", this); //réponse : screenshot
	    imessage["BIG_SCREENSHOT"]= new Img_Message("BIG_SCREENSHOT", this);
	    /* */
	    message["SEND_CMD"] = new Message("SEND_CMD", "1s1a", this);
	    message["RES_CMD"]  = new Message("RES_CMD", "1s1a", this);
    
	    message["TEST"] = new Message("TEST", "1s1s", this);
	    message["RETOUR"] = new Message("RETOUR", "1s1s", this);
	    message["OK"] = new Message("OK", "1s", this);
	    message["ERR"] = new Message("ERR", "1s", this);
	    
    
	}
    };
};

#endif
