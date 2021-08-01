#include "hachage.h"
#include "interface.h"

T_Hachage::T_Hachage()
{
    taille=0;
    tab=new mots*[MAXTAB+1];
    for(int i=0;i<MAXTAB+1;i++)
    {
        tab[i]=new mots;
        tab[i]=nullptr;
    }
}

/*
QAbstractItemModel *mff(const QString& fileName)
{
    QFile file(fileName);

    if (!file.open(QFile::ReadOnly))
    {
        //qDebug<<"echeccc open file";
    }
    else{
    QStringList words;

    while (!file.atEnd())
    {
        QByteArray line = file.readLine();

        if (!line.isEmpty())
            words << line.trimmed();
    }


    return new QStringListModel(words);
    }
}


void autocompletion()
{
    QLineEdit * lineEdit = new QLineEdit (this );

    QCompleter * completer = new QCompleter (this );
    completer->setModel(mff("dico.txt"));
    completer -> setCaseSensitivity ( Qt :: CaseInsensitive);
    lineEdit -> setCompleter(completer);
}*/


T_Hachage::~T_Hachage()
{
    if(tab!=nullptr)
    {
        for(int i=0;i<MAXTAB+1;i++)
            if(tab[i]!=nullptr)
                delete tab[i];
        delete tab;
    }
}


void T_Hachage::vider()
{
   /* if(tab!=nullptr)
    {
        for(int i=0;i<MAXTAB;i++)
            if(tab[i]!=nullptr)
                delete tab[i];
        delete tab;
    }*/
    taille=0;
    tab=new mots*[MAXTAB+1];
    for(int i=0;i<MAXTAB+1;i++)
    {
        tab[i]=new mots;
        tab[i]=nullptr;
    }
    dont=0;
}


/*void T_Hachage::set_element(mots* m)
{
   tab[taille]=m;
}*/


mots* T_Hachage::get_element(int i  )
{
    //qDebug () << tab[i]->get_terme();
    return tab[i];

}


int hash1(QString ch)
{
    unsigned long h=0,m=100;
    int l=ch.size();
    for(int i=0;i<ch.size();i++)
    {
        h+= ch[i].unicode() * pow(m,(l-i-1));
    }

    return (h%MAXTAB+1);
}

int hash2(QString ch)
{
    unsigned long h=ch[0].unicode();
    for(int i=1;i<ch.size();i++)
    {
        h+=pow(ch[i-1].unicode(),3)+pow(ch[i].unicode(),3)+100*ch[i].unicode()*ch[i-1].unicode();
    }
    return (h%MAXTAB+1);
}

int hash3(QString ch)
{
    unsigned long h=0,h2=0;
    int n=ch.size();
    for(int i=0;i<n;i++)
    {
        h+=ch[i].unicode()*(i+1)* 1000* pow(1,1);
        h2+=ch[n-i].unicode()*(i+1)*1000* pow(1,1);
    }
    return ((h+h2)%MAXTAB+1);

}


int T_Hachage::sondage_lineaire(QString m)
{
    int t,i=0;

    t=(f1(m)+i)%MAXTAB;
    while(tab[t]!=nullptr)
    {
        i++;
        t=(f1(m)+i)%MAXTAB;

    }
    return t;

}

int T_Hachage::sondage_quadratique(QString m)
{
    int t,i=0,n=0;
    t=(f1(m)+i)%MAXTAB;
    while(tab[t]!=nullptr)
    {
        n=i*i;
        t=(f1(m)+n)%MAXTAB;
        i++;
    }
    return t;

}


int T_Hachage::double_hachage(QString m)
{
    int i=0,t;
    t=(f1(m)+i*f2(m))%MAXTAB;
    while(tab[t]!=nullptr)
    {
        i++;
        t=(f1(m)+i*f2(m))%MAXTAB;
    }
    return t;
}

int T_Hachage::chainage_lineaire(Cmots* cm)
{
   if(tab[f1(cm->get_terme())]==nullptr)
   {
       cm->set_suiv(nullptr);
       tab[f1(cm->get_terme())]=cm;

   }
    else
    {qDebug()<<"jnckw";

            Cmots *crt=dynamic_cast<Cmots*>(tab[f1(cm->get_terme())]);
            while(crt!=nullptr&&crt->get_suiv()!=nullptr)
                crt=crt->get_suiv();
            if(crt!=nullptr){
                crt->set_suiv(cm);
            cm->set_suiv(nullptr);}
            else {
                crt=cm;
            }
    }qDebug()<<"fin";
   return 1;
}


int T_Hachage::recherche_lineaire(QString m)
{
    qDebug () << "r1";
    int t=f1(m),i=0;
    qDebug () << "r2";
    while(tab[t]!=nullptr && tab[t]->get_terme()!=m )
    {
        i++;
        t=(f1(m)+i)%MAXTAB;
    }
    if(tab[t]!=nullptr)
        return t;
    else
        return -1;
}


int T_Hachage::recherche_quadratique(QString m)
{
    qDebug () << "r1";
     int t=f1(m),n=0;
     int i=0;
     //if(i==0)
       //  i=1;
     qDebug () << "r2";
    while(tab[t]!=nullptr && tab[t]->get_terme()!=m )
    {
        qDebug () << "r3";
        n=i*i;
        qDebug () << "i" << i<< "fm" << f1(m);
        t=(f1(m)+n)%MAXTAB;
        i++;
        qDebug () << "t" << t;
    }
    qDebug () << "r4";
    if(tab[t]!=nullptr)
        return t;
    else
        return -1;
}


int T_Hachage::recherche_double(QString m)
{
    int t;int i=0;
    t=(f1(m)+i*f2(m))%MAXTAB;

    while(tab[t]!=nullptr && tab[t]->get_terme()!=m )
    {
        i++;
        t=(f1(m)+i*f2(m))%MAXTAB;
    }
    if(tab[t]!=nullptr)
        return t;
    else
        return -1;
}

Cmots* T_Hachage::recherche_chaine(QString m)
{
    //cout<<"Debut recherche"<<endl;
    Cmots*crt=dynamic_cast<Cmots*>(tab[f1(m)]);
    while((crt!=nullptr)&&(crt->get_terme()!=m))
        crt=crt->get_suiv();
    //cout<<"Fin recherche,crt="<<crt<<" "<<endl;
    return crt;

}


int T_Hachage::toutes_les_recherches(QString m)
{
    switch(sond)
    {
        case 1: return recherche_lineaire(m);
        case 2: return recherche_quadratique(m);
        case 3: return recherche_double(m);
        //case 4: return recherche_chaine(m);
    }
    return -1;
}


bool T_Hachage::inserer(mots* m)
{
    int i,j=9;
    if(!is_full())
    {
        if(tab[f1(m->get_terme())]==nullptr)
        {qDebug () <<j++ ;
            tab[f1(m->get_terme())]=m;
        }
        else
        {
            qDebug () << "case";
            qDebug () << sond;
            switch(sond)
            {

                case 1: /*k=recherche_lineaire(m->get_terme());
                        if(k!=-1)
                        {
                            return false;
                        }
                        else
                        {*/

                            qDebug () << "sl";
                            i=sondage_lineaire(m->get_terme());
                            tab[i]=m;
                       // }
                        break;
                case 2: /*k=recherche_quadratique(m->get_terme());
                        if(k!=-1)
                        {
                            return false;
                        }
                        else
                        {*/
                            qDebug () << "sq";
                           i=sondage_quadratique(m->get_terme());
                            tab[i]=m;

                        //}
                        break;
                case 3: /*k=recherche_double(m->get_terme());
                        if(k!=-1)
                        {
                            return false;
                        }
                        else
                        {*/
                            qDebug () << "dl";
                            i=double_hachage(m->get_terme());
                            tab[i]=m;

                        //}
                        break;
                default: break;
            }
        }
        taille++;
        return true;
    }
    else
    {
        return  false;
    }
}


bool T_Hachage::supprimer(QString m)
{
    int i=0;
    if(is_empty())
    {
        if(tab[f1(m)]!=nullptr)
        {
            switch(sond)
            {
                case 1: i=recherche_lineaire(m);
                        break;
                case 2: i=recherche_quadratique(m);
                        break;
                case 3: i=recherche_double(m);
                        break;
                //case 4: supprimer_chaine(m);

            }
            if(i!=-1)
            {
                delete tab[i];
                tab[i]=nullptr;
                return true;
            }
        }
        return false;
    }
    else
    {
        return false;
    }
}

void T_Hachage::conversion()
{
    for(int i=0;i<MAXTAB+1;i++)
        {
            tab[i]=new Cmots;
            tab[i]=nullptr;
            tab[i]=dynamic_cast<Cmots*>(tab[i]);
        }
}

