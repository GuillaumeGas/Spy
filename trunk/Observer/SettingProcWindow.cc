#include "SettingProcWindow.hh"

SettingProcWindow::SettingProcWindow() {
  main_layout = new QVBoxLayout;
  buttons_layout = new QHBoxLayout;

  title_label = new QLabel("Processus actuellement surveilles");
  main_layout->addWidget(title_label);

  proc_table = new QTableWidget;
  proc_table->setRowCount(2);
  proc_table->setColumnCount(1);
  QStringList lst;
  lst << "Processus";
  proc_table->setHorizontalHeaderLabels(lst);
  proc_table->verticalHeader()->setVisible(false);
  proc_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
  proc_table->setSelectionBehavior(QAbstractItemView::SelectRows);
  proc_table->setSelectionMode(QAbstractItemView::SingleSelection);

  QHeaderView *headers = proc_table->horizontalHeader();
  headers->setResizeMode(QHeaderView::Stretch);

  /* Test */
  proc_table->setItem(0, 0, new QTableWidgetItem("Firefox"));
  proc_table->setItem(0, 1, new QTableWidgetItem("Teelol"));

  main_layout->addWidget(proc_table);

  line_edit = new QLineEdit;
  button_addProc = new QPushButton("Ajouter processus");
  buttons_layout->addWidget(line_edit);
  buttons_layout->addWidget(button_addProc);
  main_layout->addLayout(buttons_layout);

  button_close = new QPushButton("Fermer");
  main_layout->addWidget(button_close);

  setLayout(main_layout);
  resize(350, 450);
  setWindowIcon(QIcon("iconSPY.png"));
  
  connect(button_close, SIGNAL(clicked()), this, SLOT(accept()));
  connect(button_addProc, SIGNAL(clicked()), this, SLOT(add_to_procTable()));
}

void SettingProcWindow::add_to_procTable() {
  QString content = line_edit->text();
  if(content.length() > 0) {
    int count = proc_table->rowCount();
    proc_table->insertRow(count);
    proc_table->setItem(0, count, new QTableWidgetItem(content));
  } else {
    QMessageBox::critical(this, "Erreur", "Le champs est vide !");
  }
}
