#include "../Common/Thread.hh"
#include <iostream>
using namespace std;

class th: public Thread<th> {

public:
    th() : Thread<th>(&th::run, this) {
    }


    void run() {
	while ( 1 ) {
	    cout << "hello " << endl;
	}
    }
};

int main() {
    th t;
    t.start();
    t.join();
    return 0;
}
