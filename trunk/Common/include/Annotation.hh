#ifndef _ANNOTATION
#define _ANNOTATION

#include <iostream>

class Annotation {

public:

    Annotation();


    enum Flags {
	INFO, ERROR, WARNING 
    };
    
    void show ( Flags , std::string );
    
    void unactive( Flags );
    void reactive( Flags );
    void unactive_all();
    void reactive_all();

private:
    
    bool active_E;
    bool active_I;
    bool active_W;

};



#endif
