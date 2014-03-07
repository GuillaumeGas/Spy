#ifndef _SESSION_MASTER_CLIENT
#define _SESSION_MASTER_CLIENT

#include <iostream>
#include "../Net.hh"
#include "proto.hh"

namespace master {

    class master_spy_co : public Client_session {
    public:	
	master_spy_co( int socket );
	
	void do_begin();
	void do_ok(std::string msg);
	void do_err(std::string msg);
	
	std::string & name();
	std::string & addr();
	int & port();
	bool & isset();


    private:
	bool m_isset;
	std::string m_name, m_addr;
	int m_port;
    };

    class master_spy_deco : public Client_session {
    public:
	master_spy_deco ( int socket );
	void do_begin();
	void do_ok( std::string msg );
	void do_err( std::string msg );
	bool & isset();
	std::string & name();
    private:
	std::string m_name;
	bool m_isset;
    };

    class master_obse : public Client_session {
    public:
	master_obse ( int socket );
	void do_begin();
	void do_ok ( std::string msg );
	void do_err ( std::string msg );
	void do_spy ( std::string msg );
	void aff_map();
	
    private:
	std::map < std::string , std::pair <std::string, int> > spy;
	
    };



    class master_cont : public Client_session {
    public:
	master_cont ( int socket );
	void do_begin();
	void do_ok ( std::string msg );
	void do_err ( std::string msg );
	void do_spy ( std::string msg );
	void aff_map();
	std::map< std::string, std::pair< std::string, int> > get_map();
	
    private:
	std::map < std::string, std::pair < std::string, int > > spy;
    };




};




#endif
