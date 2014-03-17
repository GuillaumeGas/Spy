#ifndef _SETTING_PROC_WIN
#define _SETTING_PROC_WIN

/* Classe qui affiche une fenetre proposant à l'utilisateur d'ajouter des processus à surveiller, et affiche ceux déjà enregistrés */

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QStringList>
#include <QHeaderView>
#include <QMessageBox>

#include "../Net.hh"

class SettingProcWindow : public QDialog {

    class session_on_observer;

    Q_OBJECT

    public:
    SettingProcWindow(QVector<QString> * vec_proc, Client<session_on_observer>* map_spy);

private slots:
    void add_to_procTable();

private:
    QVector<QString> * m_vec_proc;
    Client<session_on_observer>* m_map_spy;

    QVBoxLayout * main_layout;
    QHBoxLayout * buttons_layout;

    QLabel * title_label;
    QTableWidget * proc_table;
    QLineEdit * line_edit;
    QPushButton * button_addProc;
    QPushButton * button_close;

};

#endif
