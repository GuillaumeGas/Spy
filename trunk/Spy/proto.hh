#ifndef _PROTO
#define _PROTO

#include "../Net.hh"



unsigned long N = 3041567;
unsigned long e = 2656193;
unsigned long d = 2660897;





long long int expMod(long long int n, long long int p,long long  int m) {
   if (p == 0) return 1;
   int nm = n % m;
   long long int r = expMod(nm, p / 2, m);
   r = (r * r) % m;
   if (p % 2 == 0) return r;
   return (r * nm) % m;
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
    
	    message["ADD_PROC"] = new Message("ADD_PROC", "1s1s", this);
	    message["ALERT_PROC"] = new Message("ALERT_PROC", "1s1a", this);

	    message["TEST"] = new Message("TEST", "1s1s", this);
	    message["RETOUR"] = new Message("RETOUR", "1s1s", this);
	    message["OK"] = new Message("OK", "1s", this);
	    message["ERR"] = new Message("ERR", "1s", this);
	    
    
	}
    };
};

#endif
