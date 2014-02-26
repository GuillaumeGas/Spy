#ifndef _CLIENT
#define _CLIENT

/**
 * Classe permettant de gérer un client facilement à l'aide 
 * d'un protocole et de signaux boost
 *
 */

#include <iostream>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

#include "Thread.hh"
#include "Stream_net.hh"

class Client {
public:
  Client(int argc, char** argv);
  ~Client();

  int get_sock()const;
  bool stop()const;

  void boucle_cmd();

private:
  int init_network();
  int check_args(int argc, char** argv);
  void error(std::string msg)const;
  void info(std::string msg)const;

  std::string m_host;
  int m_port;
  int m_sock;
  struct sockaddr_in m_sin;
  bool m_stop;
};

/**
 *  Classe threadée permettant la reception des messages
 **/

class ThRecv : public Thread<ThRecv> {
public:
  ThRecv(Client * cli) : Thread<ThRecv>(&ThRecv::run, this), m_cli(cli) {
  }

  void run() {
    while(!m_cli->stop()) {
      Stream_net m(m_cli->get_sock());
      std::string str;
      m >> str;
      if(str.length() != 0) {
	std::cout << "[" << m_cli->get_sock() << "] : " << str << std::endl;
      }
    }
    std::cout << "Fin boucle reception" << std::endl;
  }

private:
  Client * m_cli;
};

#endif
