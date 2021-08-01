#ifndef MOTS_H
#define MOTS_H
#include <QString>
#include<iostream>

using namespace std;

class Cmots;

class mots
{
    public:
        mots();
        mots(QString,QString);
        virtual ~mots();
        mots(const mots&);
        //mots(const Cmots&);
        void affiche();
        QString& get_terme(){return terme;}
        QString& get_def(){return def;}


    protected:
        QString terme;
        QString def;
};

class Cmots:public mots
{
    public:
        Cmots();
        Cmots(QString,QString);
        ~Cmots();
        Cmots(const Cmots&);
        Cmots(const mots&);
        Cmots*get_suiv(){return suiv;}
        void set_suiv(Cmots*cm){suiv=cm;}


        private:
        Cmots*suiv;
};
#endif // MOTS_H
