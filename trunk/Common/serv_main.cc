#include "Server.hh"
#include "Serv_session.hh"
#include "Stream_net.hh"



int main(int argc, char ** argv) {
    Stream_net m(10);
    std::string s("salut1s1i5c");
    m << s.c_str();
    m.show_list();
    m <<  "jean-claude";
    m.show_elem();
}
