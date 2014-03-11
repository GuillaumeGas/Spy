#ifndef _IMG_MESSAGE
#define _IMG_MESSAGE

#include <iostream>
#include "Stream_net.hh"
#include "Serv_session.hh"
#include <boost/signals2.hpp>

using boost::signals2::signal;

class Img_Message : public Anc_Message{
public:

    Img_Message( std::string nom, Protocol * s);
    void operator()(std::string  , int , int  );
    
    std::string get_name();

    void recv ( );

    signal<void(std::string, int h, int l)> sig_recv;
    signal < void ( Img_Message & ) > p_recv;
    signal<void(Img_Message&, std::string , int  , int  )> sig_send;
    
private:    
    std::string m_name;
};


#endif
