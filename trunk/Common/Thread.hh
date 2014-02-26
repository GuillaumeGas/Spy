#ifndef _THREAD
#define _THREAD

#include <boost/thread.hpp>
#include <vector>

template <typename T>
class Thread {

public:

    Thread( void(T::*fct)(), T * fils) {
	m_fils = fils;
	m_fct = fct;
    }

    void start() {
	my_th.push_back(new boost::thread(boost::bind(m_fct, m_fils)));
    }


    void other(void(T::*fct)()) {
	my_th.push_back(new boost::thread(boost::bind(fct, m_fils)));
    }

    void join() {
	for ( int i = 0 ; i < my_th.size() ; i++ ) {
	    my_th[i]->join();
	}
    }

private:
    
    void(T::*m_fct)();
    T * m_fils;
    std::vector<boost::thread *> my_th;
};


#endif
