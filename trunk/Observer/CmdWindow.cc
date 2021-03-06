#include "CmdWindow.hh"
#include "client.hh"
#include "../Spy/MsgBox.hh"

using namespace std;

namespace observer {
    CmdWindow::CmdWindow(QString _station, Client<session_on_observer>* client) : pos(0), m_station(_station), m_client(client) {

	main_layout = new QVBoxLayout;

	title_label = new QLabel("<h1 align=\"center\">Ligne de commande - Poste " + _station + "</h1>");
	main_layout->addWidget(title_label);

	text_edit = new QTextEdit;
	text_edit->setStyleSheet("QTextEdit{background-color:black;color:white;font-family:courier;}");
	main_layout->addWidget(text_edit);

	line_edit = new QLineEdit;
	line_edit->setStyleSheet("QLineEdit{background-color:black;color:white;font-family:courier;}");
	main_layout->addWidget(line_edit);

	button_close = new QPushButton("Fermer");
	main_layout->addWidget(button_close);

	setLayout(main_layout);
	setWindowIcon(QIcon("iconSPY.png"));
	resize(650, 450);
  
	connect(button_close, SIGNAL(clicked()), this, SLOT(accept()));

	line_edit->setFocus();
    }

    void CmdWindow::exec_cmd() {
	std::string cmd = (line_edit->text()).toStdString();
	cmd += " //end//";
	cout << "CMD : " << cmd << endl;
	//m_cmd.exec(cmd.c_str());
	/*std::string res = m_cmd.get_res();
	  std::stringstream content; 
	  content << res << "\n<" << m_station.toStdString() << " " << m_cmd.get_path() << "> ";
	  text_edit->append(QString(content.str().c_str()));*/
	lst_cmd.push_back(line_edit->text());
	pos = lst_cmd.size();
	m_client->_session().proto->operator[]("SEND_CMD")(cmd);
    }

    void CmdWindow::set_cmd(QString data) {
	cout << "SUPER TEST"<< endl;
	//MsgBox::info(data.toStdString());
	text_edit->append(data);
    }

    void CmdWindow::keyPressEvent(QKeyEvent *event) {
	switch(event->key()) {
	case Qt::Key_Return:
	    exec_cmd();
	    line_edit->clear();
	    break;
	case Qt::Key_Up:
	    line_edit->setText(get_prev_cmd());
	    break;
	case Qt::Key_Down:
	    line_edit->setText(get_next_cmd());
	    break;
	}
    }

    QString CmdWindow::get_prev_cmd() {
	if(lst_cmd.size() > 0) {
	    if((pos - 1) >= 0) {
		return lst_cmd[--pos];
	    } else {
		return line_edit->text();
	    }
	} else {
	    return line_edit->text();
	}
    }

    QString CmdWindow::get_next_cmd() {
	if(lst_cmd.size() > 0) {
	    if((pos + 1) < lst_cmd.size()) {
		return lst_cmd[++pos];
	    } else {
		return "";
	    }
	} else {
	    return "";
	}
    }
};
