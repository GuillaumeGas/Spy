#ifndef _THREAD
#define _THREAD

#include <boost/thread.hpp>


template <typename T>
class Thread {

public:

    Thread( void(T::*fct)(), T * fils) {
	m_fils = fils;
	m_fct = fct;
    }

    void start() {
	my_th = new boost::thread(boost::bind(m_fct, m_fils));
    }

    void join() {
	my_th->join();
    }

private:
    
    void(T::*m_fct)();
    T * m_fils;
    boost::thread * my_th;
};


#endif
