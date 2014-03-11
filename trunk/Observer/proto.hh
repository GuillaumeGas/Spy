#ifndef _PROTO
#define _PROTO

#include "../Net.hh"

class proto_observer : public Protocol {
public:
  proto_observer(int socket) : Protocol(socket) {
    message["info"]          = new Message("info", "1s1a", this);
    message["warning"]       = new Message("warning", "1s1a", this);
    message["get_list_proc"] = new Message("get_list_proc", "1s", this); //demande la liste de processu actifs
    message["list_proc"]     = new Message("list_proc", "1s1a", this); //réponse : liste processus actifs
  }
};

#endif
