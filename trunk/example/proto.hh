#ifndef _PROTO
#define _PROTO

#include "../Net.hh"

class proto1 : public Protocol {
public:

    proto1(int socket) : Protocol(socket) {
	message["salut"] = new Message("salut", "1s3i", this);
	message["ERR"] = new Message("ERR", "1s1a", this);
	imessage["IMG1"] = new Img_Message("IMG1", this);
    }
    
    
};

#endif
