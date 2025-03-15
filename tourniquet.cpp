#include "tourniquet.h"
#include <QThread>
#include <QApplication>


Tourniquet::Tourniquet(){

    tabProcessus = (Processus**)malloc(NB_PROCESSUS * sizeof(Processus*));
    for(int i = 0; i < NB_PROCESSUS; i++)
    {
        tabProcessus[i] = nullptr;
    }

    actifProcesseur = nullptr;
    actifDisque = nullptr;

    compteur = 0;

}
Tourniquet::~Tourniquet(){

}

void Tourniquet::ajouterProcessus(Processus* p)
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



void Tourniquet::misAJourElu(File *F1, File *F2, Processus* actif1, Processus* actif2, int sens , int QUANTUM  ){

    if(actif1 == nullptr)
    {
        if(!F1->est_vide()){
            actif1 = F1->defiler();
            if(sens == 1)
            {
                actif1->setElu(true);
                actif1->setPret(false);
                std::cout<< actif1->getPid()<<" en execution1\n";
                compteur++;
            }
            else
            {
                actif1->setBloque(true);
                actif1->setEntreeSortie(true);
                std::cout<< actif1->getPid()<<" en entree/sortie1\n";
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
                F2->enfiler(*actif1);
                actif1 = nullptr;
            }
            if(sens == 1){
                compteur = 0;
            }


            if(!F1->est_vide()){
                actif1 = F1->defiler();
                actif1->calcul();

                if(sens == 1)
                {
                    actif1->setElu(true);
                    actif1->setPret(false);
                    std::cout<< actif1->getPid()<<" en execution2\n";
                    compteur++;
                }
                else
                {
                    actif1->setBloque(true);
                    actif1->setEntreeSortie(true);
                    std::cout<< actif1->getPid()<<" en entree/sortie2\n";
                }
            }

        }
        else  if (actif1->getScenario()->val == 0 && actif1->getScenario()->suivant == nullptr)
        {
            // std::cout <<"                                       "<<actif1->getPid()<<" a termine\n";
            delete actif1;
            actif1 = nullptr;
            if(sens == 1){
                compteur = 0;
            }

            if(!F1->est_vide()){
                actif1 = F1->defiler();
                actif1->calcul();

                if(sens == 1)
                {
                    actif1->setElu(true);
                    actif1->setPret(false);
                    std::cout<< actif1->getPid()<<" en executio3\n";
                    compteur++;
                }
                else
                {
                    actif1->setBloque(true);
                    actif1->setEntreeSortie(true);
                    std::cout<< actif1->getPid()<<" en entree/sortie3\n";
                }
            }
        }
        else
        {
            if(sens == 1 && compteur == QUANTUM)
            {
                Processus *tmp = actif1;

                if(!F1->est_vide()){
                    actif1 = F1->defiler();

                    actif1->setElu(true);
                    actif1->setPret(false);
                }
                tmp->setElu(false);
                tmp->setPret(true);

                F1->enfiler(*tmp);

                compteur = 0;
            }
            actif1->calcul();
            if(sens == 1)
            {
                std::cout<< actif1->getPid()<<" en execution4\n";
                compteur++;
            }
            else
                std::cout<< actif1->getPid()<<" en entree/sortie4\n";
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
}

#include <QTimer>
void Tourniquet::executionTourniquet(QTableWidget* tab1, QTableWidget* tab2, QTableWidget* tab3, QTableWidget* tab4 , int qt) {
    int* i = new int(0);  // Pointer to track time
    int* j = new int(0);  // Pointer to track process count

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
                    tabProcessus[k]->setPret(true);
                    (tabProcessus[k]->getScenario()->type_operation == 0)
                        ? fileProcessusPret.enfiler(*tabProcessus[k])
                        : fileProcessusDisque.enfiler(*tabProcessus[k]);
                    (*j)++;
                }
            }
        }

        // Mise à jour des processus actifs
        misAJourElu(&fileProcessusPret, &fileProcessusDisque, actifProcesseur, actifDisque, 1 , qt );
        misAJourElu(&fileProcessusDisque, &fileProcessusPret, actifDisque, actifProcesseur, 2 , qt );

        // Mettre à jour le chronogramme
        remplirChronogramme(tab1, tab2, tab3, tab4, fileProcessusPret, fileProcessusDisque, actifProcesseur, actifDisque, *i);

        // Vérifier si tout est terminé
        if (fileProcessusPret.est_vide() && fileProcessusDisque.est_vide() && !actifProcesseur && !actifDisque) {
            timer->stop();
            delete i;
            delete j;
            timer->deleteLater();
            return;
        }

        (*i)++;  // Increment time
    });

    timer->start(100);  // Exécute toutes les 250 ms
}

void Tourniquet::executionTourniquet1(QTableWidget* tab1 , QTableWidget* tab2 , QTableWidget* tab3 , QTableWidget* tab4 , int QUANTUM){

    int i = 0, j = 0;

    while(i < MAX){

        if(j < NB_PROCESSUS)
        {
            for(int k = 0; k < NB_PROCESSUS; k++){
                if(tabProcessus[k]->getDateArrivee() == i)
                {
                    tabProcessus[k]->setPret(true);
                    (tabProcessus[k]->getScenario()->type_operation == 0)
                        ? fileProcessusPret.enfiler(*tabProcessus[k])
                        : fileProcessusDisque.enfiler(*tabProcessus[k]);
                    j++;
                }
            }
        }
        //QThread::msleep(250) ;

        //QCoreApplication::processEvents() ;


        misAJourElu(&fileProcessusPret, &fileProcessusDisque, actifProcesseur, actifDisque, 1 , QUANTUM);

        misAJourElu(&fileProcessusDisque, &fileProcessusPret, actifDisque, actifProcesseur, 2 , QUANTUM);

        remplirChronogramme( tab1 , tab2 ,  tab3 ,  tab4  ,fileProcessusPret,fileProcessusDisque, actifProcesseur,actifDisque , i ) ;

        if(fileProcessusPret.est_vide() && fileProcessusDisque.est_vide() && !actifProcesseur && !actifDisque)
        {

            break;
        }

        i++;

    }

}


void Tourniquet::remplirChronogramme( QTableWidget* tab1 , QTableWidget* tab2 , QTableWidget* tab3 , QTableWidget* tab4 ,File fileP, File fileD, Processus *actifP, Processus *actifD , int col ){
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


