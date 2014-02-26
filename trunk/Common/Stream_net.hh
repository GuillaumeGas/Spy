#ifndef _STREAMNET
#define _STREAMNET


/*pour definir le flux facilement */
/* TODO */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <pthread.h>
#include <iostream>
#include <typeinfo>
#include <list>
#include <vector>
#include <sstream>

struct typewait {
    typewait(std::string t, int n) : type(t), nb(n) {}
    typewait(char * t, int n) : type(t), nb(n) {}
    typewait(char t, int n) : nb(n) { type = t;}
    std::string type;
    int nb;
};

template <typename T>
struct typeelem {
    typeelem(T e): elem(e){}
    T elem;
};

class Stream_net {
public:

    Stream_net(int sock);
    
    void send_string( const char * param );
    void send_int( int param );
    void send_char( int param );
    
    void show_list();
    void show_elem();
    void send_msg();

private:

    std::list<typewait> m_waited_elem;
    std::stringstream ss;
    FILE * m_read;
    FILE * m_write;
    
};


template <typename T>
Stream_net & operator<<( Stream_net & st, T param ) {
    std::string name = typeid(T).name();
    if ( name == "i" ) {
       
    } else if ( name == "c" ) {
    	
    } else if ( name == "PKc" ) {
	st.send_string(param);
    } else {
	std::cout << name << ": " << param << std::endl;
    }
    return st;
}
Stream_net & operator<<( Stream_net & st, std::string param);



#endif
