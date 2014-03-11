#ifndef _PROTO
#define _PROTO

#include "../Net.hh"

class proto_observer : public Protocol {
public:
  proto_observer(int socket) : Protocol(socket) {
    message["info"] = new Message("info", "1s1a", this);
    message["warning"] = new Message("warning", "1s1a", this);
  }
};

#endif
