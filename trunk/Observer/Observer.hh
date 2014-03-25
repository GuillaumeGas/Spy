#ifndef _OBSERVER
#define _OBSERVER

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>

#include <QApplication>
#include <QMainWindow>
#include <QStringList>
#include <QString>
#include <QInputDialog>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVector>
#include <QMap>
#include <QString>
#include <QScrollArea>
#include <QDesktopWidget>

#include "../Net.hh"
#include "../Master/client.hh"
#include "Miniature.hh"
#include "MessageWindow.hh"
#include "SettingProcWindow.hh"
#include "client.hh"

namespace observer {
    class Observer : public QMainWindow{

	Q_OBJECT

	public:
	Observer(int argc, char** argv);
	Observer( std::string, int );
	bool ask_room();
	void Init_all();
	std::map <std::string, Client<session_on_observer> * > & get_map_client();
	QMap<QString, Miniature*> &get_map_stations();
	std::map<std::string, std::pair<std::string, int> > & get_map();	       

	void update_img_screenshot(std::string, std::string);
	void proc_detected(std::string);
	void lst_proc_recved(QString, QMap<int, QString>);
	void res_cmd_recved(std::string, std::string);

    signals:
	void sig_set_screen(QString, QString);
	void sig_reset_style();

		       
    private slots:
	void change_room_slot();

    
    private:
	QString m_room;
	QVector<QString> m_lst_proc; //list proc a surveiller
	std::map<std::string, std::pair<std::string, int> > map_spy_info;

	/* Elements d'affichage */
	QWidget * window;
	MessageWindow * message_window; //Fenetre type QDialog pour envoyer msg aux etu
	SettingProcWindow * setting_proc_win;

	QVBoxLayout * main_layout;
	QHBoxLayout * menu_layout;
	QGridLayout * grid_layout;
	QScrollArea * scroll; //contient le content
	QWidget     * content; //contient le grid_layout

	QLabel * title;
	QPushButton * button_sendMsg;
	QPushButton * button_changeRoom;
	QPushButton * button_settingProc;
	QPushButton * button_quit;
  
	QMap<QString, Miniature*> map_stations;
	/* Fin éléments d'affichage */

	void create_window();
	void create_title();
	void create_menu();
	void create_grid();
	void create_connections(); //connect les boutons...
	void init_data();

	void update_screenshots();


	Client<master::master_obse> cli_master;
	std::map<std::string, Client<session_on_observer>* > map_spy;

    };
};

#endif
