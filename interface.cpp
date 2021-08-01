#include "interface.h"


interface::interface():QWidget()
{
    dico_db = QSqlDatabase::addDatabase("QSQLITE");
    dico_db.setDatabaseName("dicobd.db");
    if(dico_db.open()==false)
        qDebug () << "bd pas ouverte";
    layout=new QGridLayout;
    layout->setContentsMargins(0,0,0,0);
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->setHorizontalSpacing(-1);
    layout->setVerticalSpacing(-1);
    //for(int i=0;i<10;i++)
      //     label[i]=new QLabel;
    /*for(int i=0;i<1500;i++)
    {
          button[i]=new QPushButton("antigouvernementalisation");
          connect(button[i],&QPushButton::clicked,[=](){emit definition(i);});
          l->addWidget(button[i],j++,0);
    }*/
    //layout->addWidget(label[2],2,2,1,1);
    
    plage_defi=nullptr;
    scrollArea=nullptr;
    contient=nullptr;
    l=nullptr;
    label[1]=nullptr;
    recherche=nullptr;
    ok=nullptr;
    retour=new QPushButton("retour");
    retour->setFixedSize(50,20);
    layout->addWidget(retour,2,0);
    connect(retour,SIGNAL(clicked()),this,SLOT(charger()));
    retour->hide();

    table_hachage.f1=nullptr;
    table_hachage.f2=nullptr;
    table_hachage.sond=0;
    layout->setRowStretch(0,0);
    this->setFixedSize(1000, 600);
    this->setStyleSheet("background-color: #FFE895");
}


interface::~interface()
{
    for(int i=0;i<1500;i++)
    {
        if(button[i]!=nullptr)
            delete button[i];
    }
    for(int i=0;i<10;i++)
        if(label[i]!=nullptr)
            delete label[i];
    for(int i=0;i<15;i++)
        if(action[i]!=nullptr)
            delete action[i];
    if(layout!=nullptr)
        delete layout;
    if(l!=nullptr)
        delete l;
    dico_db.close();
    dico_db.removeDatabase("dicobd.db");
}


QWidget* interface::creer_entete()
{
    entete=new QWidget;
    QHBoxLayout *h=new QHBoxLayout;
    QLabel *logo=new QLabel("logo");
    QLabel *titre=new QLabel("Dictionnaire Multilingue");
    QPixmap photo("tn_dico.png");
    QPixmap photo1=photo.scaled(QSize(35,35),Qt::IgnoreAspectRatio);
    logo->setStyleSheet("color: #7F0203");
    logo->setPixmap(photo1);
    logo->setFont(QFont("Comic Sans MS", 12));
    titre->setText("Dictionnaire");
    titre->setFont(QFont("Comic Sans MS", 12));
    titre->setStyleSheet("color: #FFFCAA");
    h->addWidget(logo);
    h->addWidget(titre);
    entete->setLayout(h);
    entete->setFixedSize(1000,40);
    entete->setStyleSheet("background-color: #7F0203");
    return entete;
}


void interface::page_accueil()
{
    table_hachage.version=1;
    layout->addWidget(creer_entete(),0,0,1,5);
    layout->addWidget(creer_menu(),1,0,1,5);
    label[3]=new QLabel;
    label[3]->setText("");
    label[3]->setFont(QFont("Comic Sans MS", 12));
    layout->addWidget(label[3],2,2,1,3);
    /*label[1]->hide();
    //label[2]->hide();
    scrollArea->hide();
    plage_defi->hide();
    recherche->hide();
    ok->hide();*/
    this->setLayout(layout);
}


QMenuBar* interface::creer_menu()
{
   // QHBoxLayout *hmenu=new QHBoxLayout;
    menubar=new QMenuBar(nullptr);
    QMenu *Table=new QMenu;
    QMenu *Version=new QMenu;
    Dico=new QMenu;
    QMenu *funchash=new QMenu;
    QMenu *methcol=new QMenu;
    QMenu *help=new QMenu;

    Table=menubar->addMenu("&Table");
    Table->setStyleSheet("color: #7F0203");
    Dico=menubar->addMenu("&Dictionnaire");
    Dico->setStyleSheet("color: #7F0203");
    Dico->setEnabled(false);
    funchash=menubar->addMenu("&Fonction Hachage");
    funchash->setStyleSheet("color: #7F0203");
    methcol=menubar->addMenu("&Methode de collision");
    methcol->setStyleSheet("color: #7F0203");
    Version=menubar->addMenu("&Version");
    Version->setStyleSheet("color: #7F0203");
    help=menubar->addMenu("&Aide");
    help->setStyleSheet("color: #7F0203");
    QActionGroup *func_action=new QActionGroup(this);
    func_action->setExclusive(true);
    QActionGroup *sond_action=new QActionGroup(this);
    sond_action->setExclusive(true);
    QActionGroup *Vers_action=new QActionGroup(this);
    sond_action->setExclusive(true);
    action[0]=new QAction("&Quitter",this);
    action[1]=new QAction("&Charger",this);
    action[2]=new QAction("&Hash1 ",func_action);
    action[3]=new QAction("&Hash2 ",func_action);
    action[4]=new QAction("&Hash3 ",func_action);
    action[5]=new QAction("&sondage linaire",sond_action);
    action[6]=new QAction("&sondage quadratique",sond_action);
    action[7]=new QAction("&double hachage",sond_action);
    action[8]=new QAction("&chainage lineaire",sond_action);
    action[9]=new QAction("&Sauvegarder",this);
    action[10]=new QAction("&Rechercher",this);
    action[11]=new QAction("&Rechercher tout",this);
    action[12]=new QAction("&Inserer",this);
    action[13]=new QAction("&Supprimer",this);
    action[14]=new QAction("&Aide",this);
    action[15]=new QAction("&French only",Vers_action);
    action[16]=new QAction("&FR-ANG",Vers_action);
    action[17]=new QAction("&ANG-FR",Vers_action);
    Table->addAction(action[1]);//charger 1
    Table->addAction(action[9]);//sauv 9
    action[9]->setEnabled(false);
    action[14]->setEnabled(false);
    Table->addAction(action[0]);//quitter 0
    Dico->addAction(action[10]);//find 10
    Dico->addAction(action[11]);//find all 11
    Dico->addAction(action[12]);//insert 12
    Dico->addAction(action[13]);//supprimer 13
    help->addAction(action[14]);//aide
    action[2]->setCheckable(true);//hash 1 2
    action[3]->setCheckable(true);//hash 2 3
    action[4]->setCheckable(true);//hash 3 4
    funchash->addAction(action[2]);
    funchash->addAction(action[3]);
    funchash->addAction(action[4]);
    action[5]->setCheckable(true);//sond_line  5
    action[6]->setCheckable(true);//sond_quad  6
    action[7]->setCheckable(true);//doub_hach  7
    action[8]->setCheckable(true);//chaine_line 8
    methcol->addAction(action[5]);
    methcol->addAction(action[6]);
    methcol->addAction(action[7]);
    methcol->addAction(action[8]);
    action[15]->setCheckable(true);//fr 15
    action[16]->setCheckable(true);//fr ang  16
    action[17]->setCheckable(true);//ang fr  17
    Version->addAction(action[15]);
    Version->addAction(action[16]);
    Version->addAction(action[17]);

    connect(action[0],SIGNAL(triggered()),qApp,SLOT(quit()));
    connect(action[1],SIGNAL(triggered()),this,SLOT(charger()));
    connect(action[9],SIGNAL(triggered()),this,SLOT(sauvegarder()));
    connect(action[10],SIGNAL(triggered()),this,SLOT(rechercher()));
    connect(action[11],SIGNAL(triggered()),this,SLOT(trouver_tout()));
    connect(action[12],SIGNAL(triggered()),this,SLOT(inserer()));
    connect(action[13],SIGNAL(triggered()),this,SLOT(supprimer()));
    connect(action[14],SIGNAL(triggered()),this,SLOT(aide()));
    menubar->setFixedSize(1000,30);
    menubar->setStyleSheet("color: #7F0203");
    //hmenu->
   // hmenu->setMenuBar(menubar);
    return menubar;
}


void interface::aide()
{
    QString s="Pour manipuler le dictionnaire vous disposez de deux manieres de proceder.\nI)Charger l'ancienne sauvegarde.\nAppuyer directement sur charger dans Table\n II)Changer une nouvelle fonction\n 1)Choisir une fonction de hachage dans Fonction Hachage\n2)Choisir une methode de collision dans Methode de collision\n3)Choisir une version dans version\n4)Charger dans Table\n Version par defaut francais.\nfonction par defaut hash1\ncollision par defaut sondage lineaire";
    plage_defi=new QTextEdit;
    plage_defi->setStyleSheet("background-color: beige");
    plage_defi->setFixedSize(400,400);
    plage_defi->setFont(QFont("Comic Sans MS", 12));
    layout->addWidget(plage_defi,3,2,5,3);
    plage_defi->setText(s);
}


void interface::trouver()
{
    scrollArea->hide();
    plage_defi->setText("");
    plage_defi->show();
    label[1]->show();
    recherche->show();
    ok->show();
    connect(ok,SIGNAL(clicked()),this,SLOT(rechercher()));
}


void interface::supprimer()
{
    QString mot;
    mot=QInputDialog::getText(this,"mot","mot a supprimer").toLower();
    if(mot!="")
    {
        QSqlQuery qry;
        QString s;
        if(table_hachage.version==1)
            s="delete from dictionnaire where mot=\""+mot+"\"";
        if(table_hachage.version==2)
            s="delete from dicoangfra where mot=\""+mot+"\"";
        if(table_hachage.version==3)
            s="delete from dicofraang where mot=\""+mot+"\"";
        //s=QString::fromUtf8(s.toLatin1().constData()) ;

        int reponse = QMessageBox::question(this, "Avertissement", "Voulez-vous vraiment supprimer ce mot ?", QMessageBox ::Yes | QMessageBox::No);
        if (reponse == QMessageBox::Yes)
        {
            if(qry.exec(s))
            {
                table_hachage.supprimer(mot);
                QMessageBox::information(nullptr,"Suppression","Suppression reuissie !");
            }
            else
                QMessageBox::critical(nullptr,"Suppression","Oups quelque chose a mal tourne !");
        }
        else if (reponse == QMessageBox::No)
        {
            QMessageBox::information(nullptr,"Suppression","Suppression annulee !");
        }
    }
    else
        QMessageBox::critical(nullptr,"Suppression","Saisissez quelque chose !");
}


void interface::inserer()
{
    QString mot;
    QString def;
    mot=QInputDialog::getText(this,"mot","nouveau mot").toLower();
    def=QInputDialog::getText(this,"definition","nouvelle defiition").toLower();
    if(mot!="" && def!="")
    {
        QSqlQuery qry;
        QString s;
        if(table_hachage.version==1)
            s="insert into dictionnaire(mot,definition) values(\""+mot+"\",\""+def+"\")";
        if(table_hachage.version==2)
            s="insert into dicoangfra(mot,definition) values(\""+mot+"\",\""+def+"\")";
        if(table_hachage.version==3)
            s="insert into dicofraang(mot,definition) values(\""+mot+"\",\""+def+"\")";
        //s=QString::fromUtf8(s.toLatin1().constData()) ;

        int reponse = QMessageBox::question(this, "Avertissement", "Voulez-vous vraiment inserer ce mot ?", QMessageBox ::Yes | QMessageBox::No);
        if (reponse == QMessageBox::Yes)
        {
            if(qry.exec(s))
            {
                /*mots * m=new mots;
                m->get_terme()=mot;
                m->get_def()=def;
                table_hachage.inserer(m);*/
                QMessageBox::information(nullptr,"Insertion","Insertion reuissie !");

            }
            else
                QMessageBox::critical(nullptr,"Insertion","Oups quelque chose a mal tourne !");
        }
        else if (reponse == QMessageBox::No)
        {
            QMessageBox::information(nullptr,"Insertion","Insertion annulee !");
        }
    }
    else
        QMessageBox::critical(nullptr,"Insertion","Saisissez quelque chose !");
}


void interface::trouver_tout()
{

    clear_layout();
    layout->addWidget(creer_entete(),0,0,1,5);
    layout->addWidget(creer_menu(),1,0,1,5);

    plage_defi=new QTextEdit;
    scrollArea = new QScrollArea;
    contient=new QWidget;

    label[1]=new QLabel;
    Dico->setEnabled(true);
    action[9]->setEnabled(true);
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setStyleSheet("background-color: white");
    scrollArea->setWidgetResizable(false);
    recherche=new QLineEdit;
    recherche->setStyleSheet("margin-left:0");
    recherche->setFixedSize(150,30);
    recherche->setCompleter(completer);
    ok=new QPushButton("ok");
    ok->setFixedSize(30,30);
   // plage_defi->setStyleSheet("border: none");
    retour->show();
    //label[2]->setText("Definition");

    plage_defi->setStyleSheet("background-color: beige");
    plage_defi->setFixedSize(400,400);
    plage_defi->setFont(QFont("Comic Sans MS", 12));
    //label[2]->setFont(QFont("Comic Sans MS", 14));

    scrollArea->setFixedSize(200,400);
    label[1]->setText("recherche_tout:");
    label[1]->setFont(QFont("Comic Sans MS", 12));
    label[1]->setStyleSheet("background-color: #7F0203");
    label[1]->setFixedSize(100,30);
    layout->addWidget(label[1],2,3,1,1);
    layout->addWidget(scrollArea,3,0,5,1);
    layout->addWidget(plage_defi,3,2,5,3);
    layout->addWidget(recherche,2,4,1,1);
    layout->addWidget(ok,2,5,1,1);
    connect(ok,SIGNAL(clicked()),this,SLOT(find_all()));
}


void interface::find_all()
{
    layout->removeWidget(scrollArea);
    layout->removeWidget(plage_defi);
    scrollArea = new QScrollArea;
    contient=new QWidget;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setStyleSheet("background-color: white");
    scrollArea->setWidgetResizable(false);
    plage_defi=new QTextEdit;
    l=new QGridLayout;
    plage_defi->setStyleSheet("background-color: beige");
    plage_defi->setFixedSize(400,400);
    //plage_defi->setStyleSheet("border: none");
    plage_defi->setFont(QFont("Comic Sans MS", 12));
    layout->addWidget(plage_defi,3,2,5,3);
    scrollArea->setFixedSize(200,400);
    int j=0;
    int i=0,t=0,e=0;
    QString s=recherche->text().toLower();
    int k=table_hachage.toutes_les_recherches(s);
     qDebug () << "3";
    if(k!=-1||table_hachage.sond==4)
    {
        k=table_hachage.f1(s);
        e=k;
        if(table_hachage.sond!=4)
        {
            while(table_hachage.get_element(k)!=nullptr )
            {
                if(table_hachage.f1(table_hachage.get_element(k)->get_terme())==e)
                {
                     button[j]=new QPushButton(table_hachage.get_element(k)->get_terme());
                     button[j]->setStyleSheet("border: none;text-align:left; ");
                     button[j]->setFont(QFont("Comic Sans MS", 12));
                     connect(button[j],&QPushButton::clicked,[=](){emit definition2(k);});
                     l->addWidget(button[j],j,0);
                     j++;
                }
                 switch (table_hachage.sond)
                 {
                    case 1: qDebug () << "fila"; i++; k=(table_hachage.f1(s)+i)%MAXTAB; qDebug () << i <<"ki" <<k;break;
                    case 2: qDebug () << "2";int n;i++;n=i*i; k=(table_hachage.f1(s)+n)%MAXTAB;  break;
                    case 3: qDebug () << "3";t++; k=(table_hachage.f1(s)+t*table_hachage.f2(s))%MAXTAB;break;
                    //case 4: break;
                 }


            }
        }
        else
        {
            Cmots*crt=dynamic_cast<Cmots*>(table_hachage.get_element(table_hachage.f1(s)));
            while(crt!=nullptr)
            {
                button[j]=new QPushButton(crt->get_terme());
                button[j]->setStyleSheet("border: none;text-align:left; ");
                button[j]->setFont(QFont("Comic Sans MS", 12));
                connect(button[j],&QPushButton::clicked,[=](){emit definition3(crt);});
                l->addWidget(button[j],j,0);
                j++;
                crt=crt->get_suiv();
            }
        }

        contient->setLayout(l);
        scrollArea->setWidget(contient);

        layout->addWidget(label[1],2,3,1,1);
        layout->addWidget(scrollArea,3,0,5,1);

    }
    else {
         qDebug () << "5";
        plage_defi->setText("mot pas trouver ");
    }

}


void interface::definition3(Cmots* crt)
{
    plage_defi->setText(crt->get_def());
}


void interface::rechercher()
{
    qDebug () << "1";
        QString recup_mot=recherche->text().toLower();
         qDebug () << recup_mot;
         if(table_hachage.sond!=4)
         {
             int k=table_hachage.toutes_les_recherches(recup_mot);
              qDebug () << k;
             if(k!=-1)
             {
                 plage_defi->setText(table_hachage.get_element(k)->get_def());
                 qDebug () << "4";
             }
             else {
                  qDebug () << "5";
                 plage_defi->setText("mot pas trouver");
             }
              qDebug () << "6";
         }
         else
         {
             Cmots*cm=table_hachage.recherche_chaine(recup_mot);
             if(cm!=nullptr)
             {
                 plage_defi->setText(cm->get_def());
             }
             else
             {
                 plage_defi->setText("mot pas trouver");
             }
         }

}


void interface::clear_layout()
{
    layout->removeWidget(entete);
    layout->removeWidget(menubar);
    if(label[1]!=nullptr)
        layout->removeWidget(label[1]);
    if(plage_defi!=nullptr)
        layout->removeWidget(plage_defi);
    if(scrollArea!=nullptr)
        layout->removeWidget(scrollArea);
    if(recherche!=nullptr)
        layout->removeWidget(recherche);
    if(ok!=nullptr)
        layout->removeWidget(ok);
    /*entete->hide();
    menubar->hide();
    scrollArea->hide();
    plage_defi->hide();
    label[1]->hide();
    //label[2]->hide();*/
}


void interface::charger()
{
    dont=0;
    if(action[15]->isChecked())
        table_hachage.version=1;
    if(action[16]->isChecked())
        table_hachage.version=2;
    if(action[17]->isChecked())
        table_hachage.version=3;
    qDebug () << "1";
    if(action[2]->isChecked())
    {
        table_hachage.func=1;
        table_hachage.f1=hash1;
    }
    qDebug () << "2";
    if(action[3]->isChecked())
    {
        table_hachage.func=2;
        table_hachage.f1=hash2;
    }
    qDebug () << "3";
    if( action[4]->isChecked())
    {
        table_hachage.func=3;
        table_hachage.f1=hash3;
    }
    qDebug () << "4";
    if(action[5]->isChecked())
        table_hachage.sond=1;
    qDebug () << "5";
    if( action[6]->isChecked())
        table_hachage.sond=2;
    qDebug () << "6";
    if( action[7]->isChecked())
    {
        table_hachage.sond=3;
        int k=QInputDialog::getInt(this,"fonctionn","choisissez la deuxieme fonction de hachage",1,1,3);
        switch(k)
        {
            case 1:table_hachage.f2=hash1; table_hachage.func2=1;break;
            case 2:table_hachage.f2=hash2; table_hachage.func2=2;break;
            case 3:table_hachage.f2=hash3; table_hachage.func2=3;break;
            default:table_hachage.f2=hash1; table_hachage.func2=1;break;
        }
    }
    qDebug () << "7";
    if( action[8]->isChecked() )
        table_hachage.sond=4;
    if(table_hachage.f1==nullptr || table_hachage.sond==0)
     {

        QString s1,s2,s3,s4;
        QString s="select * from sauvegarde";
        QSqlQuery querry;
        querry.exec(s);
        while(querry.next())
        {

            s1=querry.value(0).toString();
            s2=querry.value(1).toString();
            s3=querry.value(2).toString();
            s4=querry.value(3).toString();
        }
        int f,so,f2,v;
        f=s1.toInt();
        so=s2.toInt();
        f2=s3.toInt();
        v=s4.toInt();
        if(f==1)
        {
            table_hachage.func=1;
            table_hachage.f1=hash1;
        }
        if(f==2)
        {
            table_hachage.func=2;
            table_hachage.f1=hash2;
        }
        if(f==3)
        {
            table_hachage.func=3;
            table_hachage.f1=hash3;
            switch (f2)
            {
                case 1:table_hachage.f2=hash1; table_hachage.func2=1;break;
                case 2:table_hachage.f2=hash2; table_hachage.func2=2;break;
                case 3:table_hachage.f2=hash3; table_hachage.func2=3;break;
                default:table_hachage.f2=hash1; table_hachage.func2=1;break;
            }
        }
        table_hachage.sond=so;
        table_hachage.version=v;
    }
    qDebug () << "8";
    dico.detruire();
    table_hachage.vider();
    clear_layout();
    layout->addWidget(creer_entete(),0,0,1,5);
    layout->addWidget(creer_menu(),1,0,1,5);
    int i=0;
    QSqlQuery qry;
    QString s;
    if(table_hachage.version==1)
        s="select * from dictionnaire order by mot";
    if(table_hachage.version==2)
        s="select * from dicoangfra order by mot";
    if(table_hachage.version==3)
        s="select * from dicofraang order by mot";
    mots mot_def;
    if(dico_db.open()==false)
        QMessageBox::critical(nullptr,"Insertion","Oups quelque chose a mal tourne !");
    else
    {
        completer=new QCompleter;
        completeur=new QStringList;
       // QMessageBox::information(nullptr,"Charge","Chargement en cours !");
        qry.exec(s);
        if(table_hachage.sond==4)
        {
            table_hachage.conversion();
            //dont=0;

        }
        Cmots**cm=new Cmots*[MAXTAB+1];
        while(qry.next())
        {
           mot_def.get_terme()=qry.value(0).toString().toLower();
           mot_def.get_def()=qry.value(1).toString().toLower();

           dico.set_element(mot_def);
           qDebug () << "adou" ;
           *completeur << dico.adress_element(i)->get_terme() ;
           //qDebug () << dico.adress_element(i)->get_def() ;
           qDebug () << table_hachage.f1(dico.adress_element(i)->get_terme()) ;
           if(table_hachage.sond!=4)
               qDebug () << table_hachage.inserer(dico.adress_element(i));
          else
          {

              cm[dont]=new Cmots;
              cm[dont]->set_suiv(nullptr);
              cm[dont]->get_terme()=dico.adress_element(i)->get_terme();
              cm[dont]->get_def()=dico.adress_element(i)->get_def();
              qDebug()<<"dont="<<dont;
              table_hachage.chainage_lineaire(cm[dont]);
              qDebug()<<"Chainage reussi!!!";
              table_hachage.get_taille()++;
              dont++;
              //break;
          }
          // if(i==10)
            //   break;
           i++;
        }
        completer->setModel(new QStringListModel(*completeur));
       /* label[1]->hide();
        recherche->hide();
        ok->hide();
        //label[2]->show();
        scrollArea->show();
        plage_defi->show();*/
        charger_interface();
        Dico->setEnabled(true);
        action[9]->setEnabled(true);
        action[14]->setEnabled(true);
    }
}


void interface::charger_interface()
{
    int j=0;
    plage_defi=new QTextEdit;
    scrollArea = new QScrollArea;
    contient=new QWidget;
    l=new QGridLayout;
    label[1]=new QLabel;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setStyleSheet("background-color: white");
    scrollArea->setWidgetResizable(false);
    recherche=new QLineEdit;
    recherche->setStyleSheet("margin-left:0");
    recherche->setFixedSize(150,30);
    recherche->setCompleter(completer);
    ok=new QPushButton("ok");
    ok->setFixedSize(30,30);
    for(int i=0;i<dico.dget_taille();i++)//dico.dget_taille()
    {
         button[i]=new QPushButton(dico.adress_element(i)->get_terme());
         button[i]->setStyleSheet("border: none;text-align:left; ");
         button[i]->setFont(QFont("Comic Sans MS", 12));
         connect(button[i],&QPushButton::clicked,[=](){emit definition(i);});
         l->addWidget(button[i],j++,0);
    }

    //label[2]->setText("Definition");

    plage_defi->setStyleSheet("background-color: beige");
    plage_defi->setFixedSize(400,400);
    plage_defi->setFont(QFont("Comic Sans MS", 12));
    //label[2]->setFont(QFont("Comic Sans MS", 14));
    contient->setLayout(l);
    scrollArea->setWidget(contient);
    scrollArea->setFixedSize(200,400);
    label[1]->setText("recherche:");
    label[1]->setFont(QFont("Comic Sans MS", 12));
    label[1]->setStyleSheet("background-color: #7F0203");
    label[1]->setFixedSize(100,30);
    retour->hide();
    layout->addWidget(label[1],2,3,1,1);
    layout->addWidget(scrollArea,3,0,5,1);
    layout->addWidget(plage_defi,3,2,5,3);
    layout->addWidget(recherche,2,4,1,1);
    layout->addWidget(ok,2,5,1,1);
    connect(ok,SIGNAL(clicked()),this,SLOT(rechercher()));
    //label[2]->setStyleSheet("background-color: #7F0203");

}


void interface::definition(int i)
{
    plage_defi->setText(dico.adress_element(i)->get_def());
}


void interface::definition2(int i)
{
    plage_defi->setText(table_hachage.get_element(i)->get_def());

}


void interface::sauvegarder()
{
    QSqlQuery qry;
    QString s1=QString::number(table_hachage.sond);
    QString s2=QString::number(table_hachage.func);
    QString s4=QString::number(table_hachage.func2);
    QString s5=QString::number(table_hachage.version);
    QString s3="delete from sauvegarde";
    qry.exec(s3);
    QString s="insert into sauvegarde(fonction,sondage,fonction2,version) values(\'"+s2+"\',\'"+s1+"\',\'"+s4+"\',\'"+s5+"\')";
    if(qry.exec(s))
        QMessageBox::information(nullptr,"Sauvegarde","Sauvegarde reuissie !");
    else
        QMessageBox::critical(nullptr,"Insertion","Oups quelque chose a mal tourne !");
}
