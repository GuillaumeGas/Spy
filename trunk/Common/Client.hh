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

using namespace std;

template <class T>
class Client {
public:
  Client(int argc, char** argv) {
    if(check_args(argc, argv) != -1) {
      if(!init_network()) {
	error("Erreur lors la connexion.");
      } else {
	info("Connexion etablie.");
	m_stop = false;

	session = new T(m_sock);
      }
    }
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

  void error(string msg)const {
    std::cout << msg << std::endl;
  }

  void info(string msg)const {
    std::cout << msg << std::endl;
  }

private:

  T * session;

  int init_network() {
    m_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(m_sock == -1) {
      error("Erreur initialisation de la socket.");
      return -1;
    } else {
      struct hostent * hostinfo = NULL;
      hostinfo = gethostbyname(m_host.c_str());
      if(hostinfo == NULL) {
	error("Erreur hostinfo");
	return -1;
      } else {
	m_sin.sin_addr   = *(struct in_addr*)hostinfo->h_addr;
	m_sin.sin_family = AF_INET;
	m_sin.sin_port   = htons(m_port);

	return 1;
      }
    }
  }

  int check_args(int argc, char** argv) {
    if(argc < 3) {
      error("- Client -\n Usage : Client [-P port] [-H host]");
      return -1;
    } else {
      int p = -1;
      for(int i = 0; i < argc; i++) {
	if(strcmp(argv[i], "-P") == 0 && i != argc-1) {
	  p = atoi(argv[i+1]);
	}    
      }

      if(p == -1) {
	error("Port non indiqué !");
	return -1;
      } else {
	m_port = p;
      }
    
      std::string h = "null";
      for(int i = 0; i < argc; i++) {
	if(strcmp(argv[i], "-H") == 0 && i != argc-1) {
	  h = argv[i+1];
	}
      }
      if(h == "null") {
	error("Host non indiqué !");
	return -1;
      } else { 
	m_host = h;
      }

      return 1;
    }
  }

  std::string m_host;
  int m_port;
  int m_sock;
  struct sockaddr_in m_sin;
  bool m_stop;
};

#endif
