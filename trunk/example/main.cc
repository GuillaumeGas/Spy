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

    template <int N>
    string get_() {
	return typeid(get<N>(t)).name();
    }

    tuple<A...> t;
    signal<void(A...)> sig;
    static const int size = sizeof...(A);
};





int main() {
    message<int, char> m;
    m.sig.connect(foo2);
    cout << message<char, int, int>::size << endl;
    m(1,'c');
}
