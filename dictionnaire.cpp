#include "dictionnaire.h"
#include <QDebug>

dictionnaire::dictionnaire()
{
    taille=0;
    termes=new mots[MAXTAB];
    if(termes)
        qDebug()<< "OK";
}


mots* dictionnaire::adress_element(int i)
{
    mots* tamp=new mots;
    tamp=&termes[i];
    return tamp;
}


void dictionnaire::set_element(mots m)
{
    termes[taille++]=m;
}


dictionnaire::~dictionnaire()
{
    if(termes!=nullptr)
        delete termes;
}


void dictionnaire::detruire()
{
    //if(termes)
      //  delete termes;
    taille=0;
    termes=new mots[MAXTAB];
}

