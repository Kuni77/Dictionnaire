#include "Mots.h"

mots::mots()
{
    //cout<<"APPEL CONSTRUCTEUR: "<<this<<endl;
}

mots::mots(QString t,QString d)
{
    terme=t;
    def=d;
}

mots::~mots()
{
    //cout<<"APPEL DESTRUCTEUR: "<<this<<endl;
}

mots::mots(const mots&m)
{
    def=m.def;
    terme=m.terme;
}

//________________________________________________________________________________________________________________________________________
Cmots::Cmots()
{
    //cout<<"APPEL CONSTRUCTEUR: "<<this<<endl;
}

Cmots::Cmots(QString t,QString d):mots(t,d)
{
    //cout<<"APPEL CONSTRUCTEUR : "<<this<<endl;
    suiv=nullptr;
}

Cmots::~Cmots()
{
    //cout<<"APPEL DESTRUCTEUR : "<<this<<endl;
}

