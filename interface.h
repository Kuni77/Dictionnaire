#ifndef INTERFACE_H
#define INTERFACE_H


#include <QTranslator>
#include <QMainWindow>
#include <QTextCodec>
#include <QLibraryInfo>
#include <QTextEdit>
#include <QDebug>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QPalette>
#include <QGridLayout>
#include <QMessageBox>
#include <QSignalMapper>
#include <sstream>
#include <QLabel>
#include <QBrush>
#include <QFormLayout>
#include <QColorDialog>
#include <iostream>
#include <QVariant>
#include <QInputDialog>
#include <QCompleter>
#include <QStringList>
#include <QLineEdit>
#include <QAbstractItemModel>
#include <QFile>
#include <QChar>
#include <QStringListModel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QScrollBar>
#include <QImage>
#include <QMenu>
#include <QMenuBar>
#include "hachage.h"
#include "dictionnaire.h"
#include <QStackedLayout>


class interface:public QWidget
{
    Q_OBJECT
    public:
        interface();
        ~interface();
        void page_accueil();
        QMenuBar* creer_menu();
        void clear_layout();
        void charger_interface();
        QWidget* creer_entete();


    private:
        QGridLayout *layout,*l;
        QWidget* contient;
        QScrollArea* scrollArea;
        QSqlDatabase dico_db;
        QPushButton* button[6000];
        QLabel *label[10];
        QAction* action[18];
        QTextEdit *plage_defi;
        T_Hachage table_hachage;
        dictionnaire dico;
        QMenuBar *menubar;
        QWidget* entete;
        QLineEdit *recherche;
        QPushButton *ok;
        QScrollArea *sc;
        QMenu *Dico;
        QStringList *completeur;
        QCompleter * completer;
        QPushButton *retour;


    public slots:
        void charger();
        void definition(int);
        void sauvegarder();
        void trouver();
        void rechercher();
        void trouver_tout();
        void inserer();
        void find_all();
        void definition2(int );
        void definition3(Cmots* );
        void supprimer();
        void aide();
};




#endif // INTERFACE_H
