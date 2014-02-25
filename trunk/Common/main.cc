#include "Thread.hh"
#include <iostream>
using namespace std;

class th: public Thread<th> {

public:
    th() : Thread<th>(&th::run, this) {
    }


    void run() {
	cout << "salut " << endl;
    }
};

int main() {
    th t;
    t.start();

    return 0;
}
