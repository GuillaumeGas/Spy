#ifndef _MUTEX
#define _MUTEX

#include <boost/thread/mutex.hpp>

class Mutex {
public:

    Mutex();

    void lock();
    void unlock();

    ~Mutex();


private:
    boost::mutex m_mutex;

};



#endif
