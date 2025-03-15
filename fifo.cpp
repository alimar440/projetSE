#include "fifo.h"
#include <QTableWidget>
#include <QDebug>
#include <QThread>
#include <QApplication>


Fifo::Fifo(){

    tabProcessus = (Processus**)malloc(NB_PROCESSUS * sizeof(Processus*));
    for(int i = 0; i < NB_PROCESSUS; i++)
    {
        tabProcessus[i] = nullptr;
    }

    actifProcesseur = nullptr;
    actifDisque = nullptr;
}
Fifo::~Fifo(){

}

void Fifo::ajouterProcessus(Processus* p)
{
    int i = 0;
    while(i < NB_PROCESSUS && tabProcessus[i] != nullptr)
    {
        i++;
    }
    if(i < NB_PROCESSUS)
    {
        tabProcessus[i] = p;
    }
}




void Fifo::misAJourElu(File *F1, File *F2, Processus* actif1, Processus* actif2, int sens){

    if(actif1 == nullptr)
    {
        if(!F1->est_vide()){
            actif1 = F1->defiler();
            if(sens == 1)
            {
                actif1->setElu(true);
                actif1->setPret(false);

            }
            else
            {
                actif1->setBloque(true);
                actif1->setEntreeSortie(true);

            }
            actif1->calcul();
        }
    }
    else
    {
        if(actif1->getScenario()->val == 0 && actif1->getScenario()->suivant != nullptr){

            if(actif2 == nullptr){

                actif2 = actif1;
                actif2->deplacer();

                if(sens == 1)
                {
                    actif1->setElu(false);
                    actif1->setBloque(true);
                    actif1->setEntreeSortie(true);
                }
                else
                {
                    actif1->setElu(true);
                    actif1->setBloque(false);
                    actif1->setEntreeSortie(false);

                }
                actif1 = nullptr;
            }
            else
            {
                actif1->deplacer();

                F2->enfiler(*actif1);
                if(sens == 1)
                {
                    actif1->setElu(false);
                    actif1->setBloque(true);
                }
                else
                {
                    actif1->setPret(true);
                    actif1->setBloque(false);
                    actif1->setEntreeSortie(false);

                }
                actif1 = nullptr;
            }
            if(!F1->est_vide()){
                actif1 = F1->defiler();
                actif1->calcul();

                if(sens == 1)
                {
                    actif1->setElu(true);
                    actif1->setPret(false);

                }
                else
                {
                    actif1->setBloque(true);
                    actif1->setEntreeSortie(true);

                }
            }
            if(actif1){
                 qDebug() <<  " PID------------"<<actif1->getPid() ;
             actif1->afficherScenario() ;
            }

        }
        else  if (actif1->getScenario()->val == 0 && actif1->getScenario()->suivant == nullptr)
        {
            std::cout <<"                                       "<<actif1->getPid()<<" a termine\n";
            Processus* actif0 = actif1 ;
            fileT.enfiler(*actif0) ;
            delete actif1;
            actif1 = nullptr;

            if(!F1->est_vide()){
                actif1 = F1->defiler();
                actif1->calcul();

                if(sens == 1)
                {
                    actif1->setElu(true);
                    actif1->setPret(false);

                }
                else
                {
                    actif1->setBloque(true);
                    actif1->setEntreeSortie(true);

                }
            }
        }
        else
        {
            actif1->calcul();

        }
    }
    if(sens == 1)
    {
        actifProcesseur = actif1;
        actifDisque = actif2;
    }
    else
    {
        actifProcesseur = actif2;
        actifDisque = actif1;
    }
    // afficher(fileProcessusPret);
    // afficher(fileProcessusDisque);
    // std::cout<<"----------------------\n";


    if(actif1){
        actif1->afficherScenario();
    }
}


void Fifo::executionFIFO1(QTableWidget* tab1 , QTableWidget* tab2 , QTableWidget* tab3 , QTableWidget* tab4,int lieu ){

   int j = 0;
   int i = 0 ;

    while(i < MAX){


        if(j < NB_PROCESSUS)
        {
            for(int k = 0; k < NB_PROCESSUS; k++){
                if(tabProcessus[k]->getDateArrivee() == i)
                {
                    (tabProcessus[k]->getScenario()->type_operation == 0)
                    ? fileProcessusPret.enfiler(*tabProcessus[k])
                    : fileProcessusDisque.enfiler(*tabProcessus[k]);
                    j++;
                }
            }
        }


        if(!lieu){
            QThread::msleep(250) ;

            QCoreApplication::processEvents() ;
        }

        misAJourElu(&fileProcessusPret, &fileProcessusDisque, actifProcesseur, actifDisque, 1);

        misAJourElu(&fileProcessusDisque, &fileProcessusPret, actifDisque, actifProcesseur, 2);

        if(fileProcessusPret.est_vide() && fileProcessusDisque.est_vide() && !actifProcesseur && !actifDisque)
        {

            break;
        }

        remplirChronogramme( tab1 , tab2 ,  tab3 ,  tab4  ,fileProcessusPret,fileProcessusDisque, actifProcesseur,actifDisque , i ) ;


        i++;

    }



}

#include <QTimer>
void Fifo::executionFIFO(QTableWidget* tab1, QTableWidget* tab2, QTableWidget* tab3, QTableWidget* tab4, int lieu) {
    int* j = new int(0);
    int* i = new int(0);

    QTimer* timer = new QTimer();

    QObject::connect(timer, &QTimer::timeout, [=]() mutable {
        if (*i >= MAX) {
            timer->stop();
            delete i;
            delete j;
            timer->deleteLater();
            return;
        }

        // Ajouter les processus arrivés
        if (*j < NB_PROCESSUS) {
            for (int k = 0; k < NB_PROCESSUS; k++) {
                if (tabProcessus[k]->getDateArrivee() == *i) {
                    (tabProcessus[k]->getScenario()->type_operation == 0)
                    ? fileProcessusPret.enfiler(*tabProcessus[k])
                    : fileProcessusDisque.enfiler(*tabProcessus[k]);
                    (*j)++;
                }
            }
        }

        // Mise à jour des processus actifs
        misAJourElu(&fileProcessusPret, &fileProcessusDisque, actifProcesseur, actifDisque, 1);
        misAJourElu(&fileProcessusDisque, &fileProcessusPret, actifDisque, actifProcesseur, 2);

        // Vérifier si tout est terminé
        if (fileProcessusPret.est_vide() && fileProcessusDisque.est_vide() && !actifProcesseur && !actifDisque) {
            timer->stop();
            delete i;
            delete j;
            timer->deleteLater();
            return;
        }

        // Mettre à jour le chronogramme
        remplirChronogramme(tab1, tab2, tab3, tab4, fileProcessusPret, fileProcessusDisque, actifProcesseur, actifDisque, *i);

        (*i)++;
    });

    timer->start(100);
}

void Fifo::remplirChronogramme( QTableWidget* tab1 , QTableWidget* tab2 , QTableWidget* tab3 , QTableWidget* tab4 ,File fileP, File fileD, Processus *actifP, Processus *actifD , int col ){
    if(actifP){

        QTableWidgetItem *item = new QTableWidgetItem("X");
        item->setForeground(QBrush(QColor("#50C878")));
        item->setTextAlignment(Qt::AlignCenter);


        switch(actifP->getPid()) {
        case 1:
            tab1->setItem(0, col, item);
            break;
        case 2:
            tab2->setItem(0, col, item);
            break;
        case 3:
            tab3->setItem(0, col, item);
            break;
        case 4:
            tab4->setItem(0, col, item);
            break;
        }


    }
    if(actifD){
        QTableWidgetItem *item = new QTableWidgetItem("X");
        item->setForeground(QBrush(QColor("#E74C3C")));
        item->setTextAlignment(Qt::AlignCenter);

        switch(actifD->getPid()) {
        case 1:
            tab1->setItem(2, col, item);
            break;
        case 2:
            tab2->setItem(2, col, item);
            break;
        case 3:
            tab3->setItem(2, col, item);
            break;
        case 4:
            tab4->setItem(2, col, item);
            break;
        }

    }
    while(!fileP.est_vide()){
        Processus tete = fileP.tete() ;

        QTableWidgetItem *item = new QTableWidgetItem("X");
        item->setForeground(QBrush(QColor("#F1C40F")));
        item->setTextAlignment(Qt::AlignCenter);

        switch(tete.getPid()) {
        case 1:
            tab1->setItem(1, col, item);
            break;
        case 2:
            tab2->setItem(1, col, item);
            break;
        case 3:
            tab3->setItem(1, col, item);
            break;
        case 4:
            tab4->setItem(1, col, item);
            break;
        }


        fileP.defiler() ;
    }
    while(!fileD.est_vide()){
        Processus tete = fileD.tete() ;

        QTableWidgetItem *item = new QTableWidgetItem("X");
        item->setForeground(QBrush(QColor("#F1C40F")));
        item->setTextAlignment(Qt::AlignCenter);

        switch(tete.getPid()) {
        case 1:
            tab1->setItem(2, col, item);
            break;
        case 2:
            tab2->setItem(2, col, item);
            break;
        case 3:
            tab3->setItem(2, col, item);
            break;
        case 4:
            tab4->setItem(2, col, item);
            break;
        }

        fileD.defiler() ;
    }
}



void Fifo::tempsFIFO0( QTableWidget* tab )
{
    if(!fileT.est_vide())
    {

        int trP1 = fileT.tete().getTempsReponse() ; int texP1 = fileT.tete().getTempsAttente() ; int tattP1 =   fileT.tete().getTempsAttente() ;      fileT.defiler() ;
        int trP2 = fileT.tete().getTempsReponse() ; int texP2 = fileT.tete().getTempsAttente() ; int tattP2 =   fileT.tete().getTempsAttente() ;      fileT.defiler() ;
        int trP3 = fileT.tete().getTempsReponse() ; int texP3 = fileT.tete().getTempsAttente() ; int tattP3 =   fileT.tete().getTempsAttente() ;      fileT.defiler() ;
        int trP4 = fileT.tete().getTempsReponse() ; int texP4 = fileT.tete().getTempsAttente() ; int tattP4 =   fileT.tete().getTempsAttente() ;      fileT.defiler() ;

        tab->setItem(2, 1, new QTableWidgetItem(trP1));     tab->setItem(2, 2, new QTableWidgetItem(tattP1));   //tab->setItem(2, 3, new QTableWidgetItem(texP1));
        tab->setItem(3, 1, new QTableWidgetItem(trP2));     tab->setItem(3, 2, new QTableWidgetItem(tattP2));   //tab->setItem(3, 3, new QTableWidgetItem(texP2));
        tab->setItem(4, 1, new QTableWidgetItem(trP3));     tab->setItem(4, 2, new QTableWidgetItem(tattP3));   //tab->setItem(4, 3, new QTableWidgetItem(texP3));
        tab->setItem(5, 1, new QTableWidgetItem(trP4));     tab->setItem(5, 2, new QTableWidgetItem(tattP4));   //tab->setItem(5, 3, new QTableWidgetItem(texP4));

    }
}

void Fifo::tempsFIFO( QTableWidget* tab , Processus **tabProcessus )
{

        int trP1 = tabProcessus[0]->getTempsReponse() ; int texP1 = tabProcessus[0]->getTempsAttente() ; int tattP1 =   tabProcessus[0]->getTempsAttente() ;
        int trP2 = tabProcessus[1]->getTempsReponse() ; int texP2 = tabProcessus[1]->getTempsAttente() ; int tattP2 =   tabProcessus[1]->getTempsAttente() ;
        int trP3 = tabProcessus[2]->getTempsReponse() ; int texP3 = tabProcessus[2]->getTempsAttente() ; int tattP3 =   tabProcessus[2]->getTempsAttente() ;
        int trP4 = tabProcessus[3]->getTempsReponse() ; int texP4 = tabProcessus[3]->getTempsAttente() ; int tattP4 =   tabProcessus[3]->getTempsAttente() ;

        tab->setItem(2, 1, new QTableWidgetItem(trP1));     tab->setItem(2, 2, new QTableWidgetItem(tattP1));   //tab->setItem(2, 3, new QTableWidgetItem(texP1));
        tab->setItem(3, 1, new QTableWidgetItem(trP2));     tab->setItem(3, 2, new QTableWidgetItem(tattP2));   //tab->setItem(3, 3, new QTableWidgetItem(texP2));
        tab->setItem(4, 1, new QTableWidgetItem(trP3));     tab->setItem(4, 2, new QTableWidgetItem(tattP3));   //tab->setItem(4, 3, new QTableWidgetItem(texP3));
        tab->setItem(5, 1, new QTableWidgetItem(trP4));     tab->setItem(5, 2, new QTableWidgetItem(tattP4));   //tab->setItem(5, 3, new QTableWidgetItem(texP4));

}





