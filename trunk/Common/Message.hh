#ifndef _MESSAGE
#define _MESSAGE


template <typename... T>
class Message {
public:

    void operator()(T... param) {
    }


    signal<void(T...)> sig_recv;

};



#endif
