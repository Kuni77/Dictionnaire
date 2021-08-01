#ifndef DICTIONNAIRE_H
#define DICTIONNAIRE_H
#include "hachage.h"

class dictionnaire
{
    public:
        dictionnaire();
        ~dictionnaire();
        int dget_taille(){return taille;}
        mots dget_element(int i){return termes[i];}
        mots* adress_element(int );
        void set_element(mots);
        void detruire();
    private:
        int taille;
        mots* termes;
};

#endif // DICTIONNAIRE_H
