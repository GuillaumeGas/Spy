#ifndef _EXCEPTION
#define _EXCEPTION

#include <exception>
#include <iostream>


class Net_Exception : public std::exception {

public :
    Net_Exception() {};
};



class Socket_Error : public Net_Exception {
public:
    Socket_Error() {std::cout << "Probleme Chargement de Socket" << std::endl;}
};


class Bind_Error : public Net_Exception{
public:
    Bind_Error() {std::cout << "Probleme de Bind change de port" << std::endl;}
};


class Listen_Error : public Net_Exception {
public:
    Listen_Error() { std::cout << "Probleme lors du Listen" << std::endl;}
};


class Host_Error : public Net_Exception {
public:
    Host_Error() { std::cout << "Probleme Host non reconnu" << std::endl;}
};


class Connect_Error : public Net_Exception {
public:
    Connect_Error() { std::cout << "Probleme de Connection" << std::endl;}
};



class Args_Error : public Net_Exception {
public:
    Args_Error() {std::cout << "Arguments Invalide" << std::endl;}
};



#endif
