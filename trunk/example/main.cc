#include <boost/signals2.hpp>
using boost::signals2::signal;

#include <iostream>
using namespace std;



void foo2(int a, char b) {
    cout << a << b << endl;
}


template < typename... A >
struct message {
    message() {
    }
    
    void operator()(A... param) {
	sig(param...);
    }

    signal<void(A...)> sig;
};




int main() {
    message<int, char> m;
    m.sig.connect(foo2);
    m(1,'c');
}
