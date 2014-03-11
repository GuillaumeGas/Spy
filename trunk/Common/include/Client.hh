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


template <class T>
class Client {
public:
  Client(int argc, char** argv) {
    if(check_args(argc, argv) != -1) {
      init_network();
      info("Connexion etablie.");
      m_stop = false;

      session = new T(m_sock);
      session->start();	    
    } else {
      error("Erreur.");
      throw argc;
    }
  }

  Client( std::string addr, int port ) {
    m_port = port;
    m_host = addr;
    if ( !init_network() ) {
      error("Erreur lors de la connexion");
    } else {
      info("Connexion etablie");
      m_stop = false;

      session = new T(m_sock);
      session->start();
    }
  }

  void join() {
    session->join();
  }


  T & _session() {
    return *session;
  }

  ~Client() { close(m_sock); }


  int get_sock()const {
    return m_sock;
  }
  bool stop()const {
    return m_stop;
  }

  T * get_session()const {
    return session;
  }

  void quit() {
    m_stop = true;
  }

  void error(std::string msg)const {
    std::cout << msg << std::endl;
  }

  void info(std::string msg)const {
    std::cout << msg << std::endl;
  }

private:

  T * session;

  void init_network() {
    m_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(m_sock == -1) {
      error("Erreur initialisation de la socket.");
      throw m_sock;
    } else {
      struct hostent * hostinfo = NULL;
      hostinfo = gethostbyname(m_host.c_str());
      if(hostinfo == NULL) {
	error("Erreur hostinfo");
	throw hostinfo;
      } else {
	m_sin.sin_addr   = *(struct in_addr*)hostinfo->h_addr;
	m_sin.sin_family = AF_INET;
	m_sin.sin_port   = htons(m_port);

	if(connect(m_sock,(struct sockaddr *)&m_sin, sizeof(struct sockaddr)) == -1) {
	  error("Erreur lors de la connexion.");
	  throw m_sin;
	}

      }
    }
  }

  int check_args(int argc, char** argv) {
    m_port = 9999;
    for(int i = 0; i < argc; i++) {
      if(strcmp(argv[i], "-P") == 0 && i != argc-1) {
	m_port = atoi(argv[i+1]);
      }    
    }
    
    m_host = "localhost";
    for(int i = 0; i < argc; i++) {
      if(strcmp(argv[i], "-H") == 0 && i != argc-1) {
	m_host = argv[i+1];
      }
    }

    return 1;
    
  }

  std::string m_host;
  int m_port;
  int m_sock;
  struct sockaddr_in m_sin;
  bool m_stop;
};

#endif
