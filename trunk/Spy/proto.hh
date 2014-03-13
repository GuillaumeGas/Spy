#ifndef _PROTO
#define _PROTO

#include "../Net.hh"

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
	    imessage["SCREENSHOT"]    = new Img_Message("SCREENSHOT", this); //réponse : screenshot
	    /* */
	    message["SEND_CMD"] = new Message("SEND_CMD", "1s1a", this);
	    message["RES_CMD"]  = new Message("RES_CMD", "1s1a", this);
    
    
	}
    };
};

#endif
