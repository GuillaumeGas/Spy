#include "Observer.hh"

using namespace std;

Observer::Observer() {

  bool room_ok = ask_room();

  if(room_ok) {
    //QMessageBox::information(this, "Information", "Vous surveillez la salle : "+m_room);
  
    create_window();
      
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

  get_screen_size();

  window = new QWidget;
  main_layout = new QVBoxLayout;
  menu_layout = new QHBoxLayout;
  grid_layout = new QGridLayout;
  content     = new QWidget;

  scroll = new QScrollArea;
 
  create_title();
  create_menu();
  create_grid();

  create_connections();

  window->setLayout(main_layout);
  setCentralWidget(window);

  setMinimumSize(1300, 800);
  //setWindowIcon(Icon(""));
  setWindowTitle("Observer");

}

void Observer::create_title() {
  title = new QLabel("<h1 align=\"center\">Observation de la salle " + m_room + "</h1>");
  main_layout->addWidget(title);
}

void Observer::create_menu() {
  button_sendMsg = new QPushButton("Envoyer un message a tous");
  button_changeRoom = new QPushButton("Changer de salle");
  button_quit = new QPushButton("Quitter");

  menu_layout->addWidget(button_sendMsg);
  menu_layout->addWidget(button_changeRoom);
  menu_layout->addWidget(button_quit);
  main_layout->addLayout(menu_layout);
}

void Observer::create_grid() {
  /*
    insertions de test
  */
  QVector<Miniature*> vec_posts(30);
  for(int i = 0; i < vec_posts.size(); i++) {
    vec_posts[i] = new Miniature;
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
  connect(button_quit, SIGNAL(clicked()), qApp, SLOT(quit()));
}

void Observer::get_screen_size() {

    QDesktopWidget *desktop = QApplication::desktop(); 
    QSize windowSize;

    screen_w = desktop->width(); //     obtenir la largeur de l'écran
    screen_h = desktop->height(); // obtenir la hauteur de l'écran

    /*    windowSize = size();              //    taille de notre fenêtre de l'application
    width = windowSize.width();
    height = windowSize.height();*/
}
