#include "Client.hh"

using namespace std;

Client::Client(int argc, char** argv) {  
  if(check_args(argc, argv) != -1) {
    if(!init_network()) {
      error("Erreur lors la connexion.");
    } else {
      info("Connexion etablie.");
      m_stop = false;

      /* test.. */
      ThRecv th(this);
      th.start();
      th.join();

      boucle_cmd();
    }
  }
}

int Client::check_args(int argc, char** argv) {
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
    
    string h = "null";
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

int Client::init_network() {
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

Client::~Client() {
  close(m_sock);
}

void Client::boucle_cmd() {
  while(!m_stop) {
    string msg;
    cin >> msg;
    Stream_net m(m_sock);
    m << msg;
  }
}

int Client::get_sock()const {
  return m_sock;
}

bool Client::stop()const {
  return m_stop;
}

void Client::error(string msg)const {
  cout << msg << endl;
}

void Client::info(string msg)const {
  cout << msg << endl;
}
