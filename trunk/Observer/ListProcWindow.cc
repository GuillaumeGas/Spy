#include "ListProcWindow.hh"
#include "client.hh"
/* Test */
#include "../Spy/Process.hh"

namespace observer {
    ListProcWindow::ListProcWindow(QString _station, Client<session_on_observer> * client) {
	main_layout = new QVBoxLayout;

	title_label = new QLabel("Processus actifs sur " + _station);
	main_layout->addWidget(title_label);

	proc_table = new QTableWidget;
	proc_table->setColumnCount(2);
	QStringList lst_h;
	lst_h << "PID" << "Processus";
	proc_table->setHorizontalHeaderLabels(lst_h);
	proc_table->verticalHeader()->setVisible(false);
	proc_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	proc_table->setSelectionBehavior(QAbstractItemView::SelectRows);
	proc_table->setSelectionMode(QAbstractItemView::SingleSelection);

	QHeaderView * headers = proc_table->horizontalHeader();
	headers->setResizeMode(QHeaderView::Stretch);

	main_layout->addWidget(proc_table);

	/* Test */
	Process pr;
	std::map<int, std::string> lst = pr.get_list_process();
	for(auto it = lst.begin(); it != lst.end(); it++) {
	    int count = proc_table->rowCount();
	    proc_table->insertRow(count);
	    proc_table->setItem(count, 0, new QTableWidgetItem(QString::number(it->first)));
	    proc_table->setItem(count, 1, new QTableWidgetItem(QString(it->second.c_str())));
	}
	/* fin test */

	button_close = new QPushButton("Fermer");
	main_layout->addWidget(button_close);

	setLayout(main_layout);
	setWindowIcon(QIcon("iconSPY.png"));
	resize(300, 400);

	connect(button_close, SIGNAL(clicked()), this, SLOT(accept()));
    }
};
