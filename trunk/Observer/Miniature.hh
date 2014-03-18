#ifndef _MINIATURE
#define _MINIATURE

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
	Miniature(const char * file); //constructeur de test
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

    public slots:
	void slot_set_screen(QString, QString);
	void slot_reset_style();

    private:

	void mouseReleaseEvent(QMouseEvent * e);

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
