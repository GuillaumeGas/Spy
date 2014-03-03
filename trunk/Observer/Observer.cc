#include "Observer.hh"

using namespace std;

Observer::Observer() {

  bool room_ok = ask_room();

  if(room_ok) {
  
    create_window();
      
  } else{
    QMessageBox::critical(this, "Erreur", "Une erreur s'est produite lors de la connexion a la salle.");
  }
}

bool Observer::ask_room() {
  /* Liste de test */
  QStringList lst;
  lst << "info21" << "info22" << "info23";

  bool ok, continuer = true;
  while(continuer) {
    m_room = QInputDialog::getItem(this, "Observateur", "Choix de la salle :", lst, 0, false, &ok);
    if(ok && !lst.isEmpty()) {
      /* On go tenter une connexion */
      QMessageBox::information(this, "Information", "Salle selectionnee : "+m_room);
      continuer = false;
    } else if(ok && lst.isEmpty()) {
      QMessageBox::critical(this, "Erreur.", "Aucune salle disponible.");
    } else {
      continuer = false;
    }
  }
  return ok;
}

void Observer::create_window() {

  window = new QWidget;
  main_layout = new QVBoxLayout;
  menu_layout = new QHBoxLayout;
  grid_layout = new QGridLayout;
  content     = new QWidget;

  scroll = new QScrollArea;
 
  create_title();
  create_menu();
  create_grid();

  message_window = new MessageWindow;
  setting_proc_win = new SettingProcWindow;

  create_connections();

  window->setLayout(main_layout);
  setCentralWidget(window);

  setMinimumSize(1300, 800);
  setWindowIcon(QIcon("iconSPY.png"));
  setWindowTitle("Observer");

}

void Observer::create_title() {
  title = new QLabel("<h1 align=\"center\">Observation de la salle " + m_room + "</h1>");
  main_layout->addWidget(title);
}

void Observer::create_menu() {
  button_sendMsg = new QPushButton("Envoyer un message a tous");
  button_settingProc = new QPushButton("Gerer processus a surveiller");
  button_changeRoom = new QPushButton("Changer de salle");
  button_changeRoom->setEnabled(false);
  button_quit = new QPushButton("Quitter");

  menu_layout->addWidget(button_sendMsg);
  menu_layout->addWidget(button_changeRoom);
  menu_layout->addWidget(button_settingProc);
  menu_layout->addWidget(button_quit);
  main_layout->addLayout(menu_layout);
}

void Observer::create_grid() {
  /*
    insertions de test
  */
  for(int i = 0; i < 30; i++) {
    vec_posts.push_back(new Miniature("img.bmp"));
  }
  /* Fin test */
  
  int x = 0, y = 0;
  for(int i = 0; i < vec_posts.size(); i++) {
    grid_layout->addLayout(vec_posts[i], x, y);
    if(y == 2) {
      x++;
      y = 0;
    } else {
      y++;
    }
  }

  content->setLayout(grid_layout);
  scroll->setWidget(content);
  main_layout->addWidget(scroll);
}

void Observer::create_connections() {
  connect(button_sendMsg, SIGNAL(clicked()), message_window, SLOT(exec()));
  connect(button_changeRoom, SIGNAL(clicked()), this, SLOT(change_room_slot()));
  connect(button_settingProc, SIGNAL(clicked()), setting_proc_win, SLOT(exec()));
  connect(button_quit, SIGNAL(clicked()), qApp, SLOT(quit()));
}

void Observer::change_room_slot() {
  bool room_ok = ask_room();

  if(room_ok) {
  
    /* Mise à jour de l'interface */
    /* ERREUR
    while(vec_posts.size() > 0) {
      Miniature * tmp = vec_posts.front();
      delete tmp;
      vec_posts.pop_front();
    }

    for(int i = 0; i < 6; i++) {
      vec_posts.push_back(new Miniature("img2.bmp"));
    }

    int x = 0, y = 0;
    for(int i = 0; i < vec_posts.size(); i++) {
      grid_layout->addLayout(vec_posts[i], x, y);
      if(y == 2) {
	x++;
	y = 0;
      } else {
	y++;
      }
      }*/

    
  } else{
    QMessageBox::critical(this, "Erreur", "Une erreur s'est produite lors de la connexion a la salle.");
  }
}
