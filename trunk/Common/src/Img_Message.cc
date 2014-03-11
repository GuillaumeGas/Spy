#include "../include/Img_Message.hh"
using namespace std;


Img_Message::Img_Message ( string name, Protocol * s) {
    m_name = name;
    sig_send.connect ( boost::bind ( &Protocol::send_img, s, _1, _2, _3, _4 ));
    p_recv.connect ( boost::bind ( &Protocol::wait_img , s , _1));
}


void Img_Message::operator()( string  content , int h , int  l ) {    
    sig_send ( *this, content , h , l);
}


string Img_Message::get_name() {
    return m_name;
}


void Img_Message::recv ( ) {
    p_recv ( *this );
}
