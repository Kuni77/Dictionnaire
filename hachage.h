#ifndef HACHAGE_H
#define HACHAGE_H
#include <iostream>
#include <math.h>
#include <functional>
//#include <QString>
#include "Mots.h"

#define MAXTAB 6001

static int dont=0;

/*struct  mots
{
    QString m;
    QString def;
};


struct  Cmots
{
    mots m;
    Cmots*suiv;
} ;
*/

typedef std::function< int(QString) > pf;
//typedef int (*pf)(QString);

//static pf f1,f2;
//static int sond;


class T_Hachage
{
    public:
        T_Hachage();
        ~T_Hachage();
        int size(){return taille;}
        int& get_taille(){return taille;}
        bool is_full(){return (taille==6000);}
        bool is_empty(){return (taille==0);}
        //void set_element(mots* );
        mots* get_element(int  );
        int sondage_lineaire(QString);
        int sondage_quadratique(QString);
        int double_hachage(QString);
        int chainage_lineaire(Cmots* cm);
        int recherche_lineaire(QString);
        int recherche_quadratique(QString);
        int recherche_double(QString);
        Cmots* recherche_chaine(QString);
        int toutes_les_recherches(QString );
        bool inserer(mots*);///inserer dans la table de hachage
        bool supprimer(QString);///supprimer un mot de la table de hachage
        bool supprimer_chaine(QString m);
        void findall(QString);
        void vider();
        void conversion();
        pf f1,f2;
        int sond;
        int func;
        int func2;
        int version;

    private:
        int taille;
        mots** tab;
};


int hash1(QString);
int hash2(QString);
int hash3(QString);


#endif // HACHAGE_H
