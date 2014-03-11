#ifndef _ANC_MESSAGE
#define _ANC_MESSAGE


#include <boost/signals2.hpp>
using boost::signals2::signal;

class Anc_Message {
public:
    virtual void recv ( ) = 0;
};




#endif
