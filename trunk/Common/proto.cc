#include "proto.hh"
using namespace std;

void message1(Stream_net & s, string name,  int a , string b) {
    s << name.c_str() << a << b.c_str();
}
