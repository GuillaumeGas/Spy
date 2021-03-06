#ifndef _MINIATURE
#define _MINIATURE

#include <iostream>

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>

#include "StationWindow.hh"

namespace observer {

    class session_on_observer;

    class Miniature : public QWidget {

	Q_OBJECT

	public:
	Miniature(const char * file, const char * post, const char * user, Client<session_on_observer> * client);

	/**
	 *  \brief Permet de modifier le style du widget courant
	 *  \param style est le style désiré
	 */
	void set_style(QString style);
	/**
	 *  \brief Permet de modifier le style lors du survol de la sourie du widget courant
	 *  \param style est le style désiré
	 */
	void set_hover_style(QString style);

	void set_img(QString file);

	void set_proc_list(QMap<int, QString> list);
	void set_cmd(QString data);

    public slots:
	void slot_cmd_recv(QString, QString);
	void slot_proc_list(QString, QString);
	void slot_proc_detected(QString);
	void slot_set_screen(QString, QString);
	void slot_reset_style();

    private:

	void mouseReleaseEvent(QMouseEvent * e);

	StationWindow * station_win;

	QVBoxLayout * main_layout;
	QLabel * m_img;
	QLabel * m_station_label;
	QLabel * m_user_label;

	QString m_station;
	QString m_user;
	Client<session_on_observer>* m_client;

    };
};
#endif
