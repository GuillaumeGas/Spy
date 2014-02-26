#include "Client_session.hh"

using namespace std;

Client_session::Client_session(int _sock) : Thread<Client_session>(&Client_session::loop_recv, this) {
  m_sock = _sock;
  m_stop = false;

  while(!m_stop) {
    string msg;
    cout << "msg : ";
    cin >> msg;
    Stream_net m(m_sock); // ERREUR
    m << "1i" << 5;
    //    send(m_sock, "test", 5, 0);
  }
}

void Client_session::loop_recv() {
  while(!m_stop) {
    Stream_net m(m_sock);
    string str;
    m >> str;
    if(str.length() != 0) {
      cout << "[" << m_sock << "] : " << str << endl;
    }
  }
  std::cout << "Fin boucle reception" << std::endl;
}

int Client_session::get_sock()const {
  return m_sock;
}

bool Client_session::IsStopped()const {
  return m_stop;
}

void Client_session::set_stop() {
  m_stop = !m_stop;
}

