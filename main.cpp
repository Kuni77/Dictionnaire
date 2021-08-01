#include "interface.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    interface fenetre;
    fenetre.page_accueil();
    fenetre.show();
   /* QSqlDatabase dico_db;
    dico_db = QSqlDatabase::addDatabase("QSQLITE");
    dico_db.setDatabaseName("dicobd.db");
    QSqlQuery qry;

    if(dico_db.open()==false)
          QMessageBox::critical(nullptr,"Connexion","La connexion a échoué !");
   else
   {
    qry.exec("create table dicoangfra(mot text,definition text)");
    int k=0,n=0;
        int cot=0;
        int i=0,m=0;

        QFile file("frang.txt");

           if (!file.open(QFile::ReadOnly))
           {
               qDebug () << "pas ouvert";
           }


        while(!file.atEnd())
        {
            QByteArray line = file.readLine();
            QString mot="";
            QString defi="" ;
            QString req="";
            QSqlQuery qry;
            if (!line.isEmpty())
            line=line.trimmed();
             n=line.size();
            for( i=0;i<n;i++)
            {
                if(line[i]==',')
                    break;
                if(line[i]==':')
                {
                    k++;
                    cot++;
                }
                if(k==0)
                {
                    if(line[i+1]!=':')
                            mot+=line[i];

                }
                if(k==1)
                {
                    if(line[i]!=':' && line[i+1]!=' ')
                        defi+=line[i];

                }

            }
            req="insert into dicoangfra(mot,definition) values(\""+defi+"\",\""+mot+"\")";
            req=QString::fromUtf8(req.toLatin1().constData()) ;
             qry.exec(req);
             k=0;
            // m++;
             //if(m==10)
               //  break;

        }

        qDebug () << cot;
    }*/
    return a.exec();
}

