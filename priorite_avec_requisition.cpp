#include "priorite_avec_requisition.h"

PrioriteAvecRequisition::PrioriteAvecRequisition(){

    tabProcessus = (Processus**)malloc(NB_PROCESSUS* sizeof(Processus*));
    for(int i = 0; i < NB_PROCESSUS; i++)
    {
        tabProcessus[i] = NULL;
    }

    actifProcesseur = NULL;
    actifDisque = NULL;
}


void PrioriteAvecRequisition::ajouterProcessus(Processus* p)
{
    int i = 0;
    while(i < NB_PROCESSUS && tabProcessus[i] != NULL)
    {
        i++;
    }
    if(i < NB_PROCESSUS)
    {
        tabProcessus[i] = p;
    }
}



void PrioriteAvecRequisition::misAJourElu(Liste *L, File *F, Processus* actif1, Processus* actif2){

    if(!L->est_vide() && actif1 != nullptr){

        Processus *tmp = L->prochainPriorite();

        if(tmp->getPriorite() > actif1->getPriorite())
        {
            if(actif1->getScenario()->val != 0)
            {
                actif1->setPret(true);
                actif1->setElu(false);

                L->ajouter(actif1);

            }
            else
            {
                if(actif1->getScenario()->suivant != NULL)
                {
                    if(actif2 != nullptr){

                        actif1->setElu(false);
                        actif1->setBloque(true);
                        actif1->deplacer();

                        F->enfiler(*actif1);
                    }
                    else
                    {

                        actif2 = actif1;
                        actif2->deplacer();

                        actif2->setElu(false);
                        actif2->setBloque(true);
                        actif2->setEntreeSortie(true);

                        std::cout<< actif1->getPid()<<" en entree/sortie6\n";

                        actif2->calcul();

                    }
                }
                else
                {
                    std::cout<< actif1->getPid()<<"                                       a termine1\n";

                    delete(actif1);
                }
            }
            actif1 = tmp;

            actif1->setElu(true);
            actif1->setPret(false);

            actif1->calcul();
            std::cout<< actif1->getPid()<<" en execution\n";
            actifProcesseur = actif1;
            actifDisque = actif2;
            return;
        }
        else
        {
            L->ajouter(tmp);
        }
    }

    if(actif1 == NULL)
    {
        if(!L->est_vide()){
            actif1 = L->prochainPriorite();

            actif1->setElu(true);
            actif1->setPret(false);
            actif1->calcul();
            std::cout<< actif1->getPid()<<" en execution1\n";
        }
    }
    else
    {
        if(actif1->getScenario()->val == 0 && actif1->getScenario()->suivant != NULL){

            if(actif2 == NULL){
                actif2 = actif1;
                actif2->deplacer();
                actif2->calcul();


                actif1->setElu(false);
                actif1->setBloque(true);
                actif1->setEntreeSortie(true);
                std::cout<< actif1->getPid()<<" en entree/sortie.5\n";
                actif1 = NULL;
            }
            else
            {
                actif1->deplacer();
                F->enfiler(*actif1);

                actif1->setElu(false);
                actif1->setBloque(true);
                actif1 = NULL;
            }
            if(!L->est_vide()){
                actif1 = L->prochainPriorite();
                actif1->calcul();


                actif1->setElu(true);
                actif1->setPret(false);
                std::cout<< actif1->getPid()<<" en execution2\n";
            }
        }
        else  if (actif1->getScenario()->val == 0 && actif1->getScenario()->suivant == NULL)
        {
            std::cout<< actif1->getPid()<<"                                       a termine1\n";
            delete actif1;
            actif1 = NULL;

            if(!L->est_vide()){
                actif1 = L->prochainPriorite();
                actif1->calcul();


                actif1->setElu(true);
                actif1->setPret(false);
                std::cout<< actif1->getPid()<<" en execution3\n";
            }
        }
        else
        {
            actif1->calcul();
            std::cout<< actif1->getPid()<<" en execution4\n";
        }
    }
    actifProcesseur = actif1;
    actifDisque = actif2;
}

void PrioriteAvecRequisition::misAJourCoteDisque(File *F, Liste *L, Processus* actif1, Processus* actif2){

    if(actif1 == NULL)
    {
        if(!F->est_vide()){
            actif1 = F->defiler();

            actif1->setBloque(true);
            actif1->setEntreeSortie(true);
            actif1->calcul();
            std::cout<< actif1->getPid()<<" en entree/sortie1\n";
        }
    }
    else
    {
        if(actif1->getScenario()->val == 0 && actif1->getScenario()->suivant != NULL){

            if(actif2 == NULL){
                actif2 = actif1;
                actif2->deplacer();


                actif1->setElu(true);
                actif1->setBloque(false);
                actif1->setEntreeSortie(false);
                actif1 = NULL;
            }
            else
            {
                actif1->deplacer();
                if(actif1->getPriorite() > actif2->getPriorite())
                {
                    if(actif2->getScenario()->val != 0)
                    {
                        actif2->setPret(true);
                        actif2->setBloque(false);
                        actif2->setEntreeSortie(false);

                        L->ajouter(actif2);
                        actif2 = actif1;

                        if(!F->est_vide())
                        {
                            actif1 = F->defiler();
                            actif1->calcul();
                            std::cout<< actif1->getPid()<<" en entree/sortie6\n";

                            actif1->setEntreeSortie(true);
                        }
                        else
                        {
                            actif1 = NULL;
                        }
                    }
                    else
                    {
                        if(actif2->getScenario()->suivant != NULL)
                        {
                            if(!F->est_vide()){

                                Processus *tmp = actif2;

                                actif2->setElu(false);
                                actif2->setBloque(true);

                                actif2 = actif1;

                                actif2->setElu(true);
                                actif2->setBloque(false);
                                actif2->setEntreeSortie(false);

                                F->enfiler(*tmp);
                                actif1 = F->defiler();
                                actif1->calcul();
                                std::cout<< actif1->getPid()<<" en entree/sortie6\n";

                                actif1->setEntreeSortie(true);
                            }
                            else
                            {
                                Processus *tmp = actif2;

                                actif2->setElu(false);
                                actif2->setBloque(true);
                                actif2->setEntreeSortie(true);

                                actif2 = actif1;

                                actif2->setElu(true);
                                actif2->setBloque(false);
                                actif2->setEntreeSortie(false);

                                actif1 = tmp;
                                actif1->deplacer();
                                std::cout<< actif1->getPid()<<" en entree/sortie6\n";

                                actif1->calcul();

                            }
                        }
                        else
                        {
                            std::cout<< actif2->getPid()<<"                                       a termine1\n";
                            delete(actif2);

                            actif2 = actif1;

                            actif2->setElu(true);
                            actif2->setBloque(false);
                            actif2->setEntreeSortie(false);

                            if(!F->est_vide())
                            {
                                actif1 = F->defiler();
                                actif1->calcul();
                                std::cout<< actif1->getPid()<<" en entree/sortie6\n";

                                actif1->setEntreeSortie(true);
                            }
                            else
                            {
                                actif1 = NULL;
                            }

                        }
                    }


                }
                else
                {

                    L->ajouter(actif1);
                    actif1->setPret(true);
                    actif1->setBloque(false);
                    actif1->setEntreeSortie(false);
                    actif1 = NULL;
                }
            }
            if(!F->est_vide()){
                actif1 = F->defiler();
                actif1->calcul();


                actif1->setBloque(true);
                actif1->setEntreeSortie(true);
                std::cout<< actif1->getPid()<<" en entree/sortie2\n";
            }
        }
        else  if (actif1->getScenario()->val == 0 && actif1->getScenario()->suivant == NULL)
        {
            std::cout<< actif1->getPid()<<"                                       a termine1\n";
            delete actif1;
            actif1 = NULL;

            if(!F->est_vide()){
                actif1 = F->defiler();
                actif1->calcul();


                actif1->setBloque(true);
                actif1->setEntreeSortie(true);
                std::cout<< actif1->getPid()<<" en entree/sortie3\n";
            }
        }
        else
        {
            actif1->calcul();
            actif1->afficherScenario();
            std::cout<< actif1->getPid()<<" en entree/sortie4\n";
        }
    }
    actifProcesseur = actif2;
    actifDisque = actif1;
}
PrioriteAvecRequisition::~PrioriteAvecRequisition(){

}

void PrioriteAvecRequisition::executionPrioriteAvecRequisition1(QTableWidget* tab1 , QTableWidget* tab2 , QTableWidget* tab3 , QTableWidget* tab4 )
{

    int i = 0, j = 0;

    while(i < MAX)
    {

        if(j < NB_PROCESSUS)
        {
            for(int k = 0; k < NB_PROCESSUS; k++){
                if(tabProcessus[k]->getDateArrivee() == i)
                {
                    (tabProcessus[k]->getScenario()->type_operation == 0)
                    ? listeProcessusPret.ajouter(tabProcessus[k])
                    : fileProcessusDisque.enfiler(*tabProcessus[k]);
                    j++;
                }
            }
        }


        misAJourCoteDisque(&fileProcessusDisque, &listeProcessusPret, actifDisque, actifProcesseur);

        misAJourElu(&listeProcessusPret, &fileProcessusDisque, actifProcesseur, actifDisque);

        remplirChronogramme( tab1 , tab2 ,  tab3 ,  tab4  ,listeProcessusPret,fileProcessusDisque, actifProcesseur,actifDisque , i ) ;


        i++;

        std::cout<<"-------------------------------------------------------------------------------------"<<i<<"\n";

    }

}
#include <QTimer>
void PrioriteAvecRequisition::executionPrioriteAvecRequisition(QTableWidget* tab1, QTableWidget* tab2, QTableWidget* tab3, QTableWidget* tab4) {
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
                    (tabProcessus[k]->getScenario()->type_operation == 0)
                    ? listeProcessusPret.ajouter(tabProcessus[k])
                    : fileProcessusDisque.enfiler(*tabProcessus[k]);
                    (*j)++;
                }
            }
        }

        // Mise à jour des processus actifs
        misAJourCoteDisque(&fileProcessusDisque, &listeProcessusPret, actifDisque, actifProcesseur);
        misAJourElu(&listeProcessusPret, &fileProcessusDisque, actifProcesseur, actifDisque);

        // Mettre à jour le chronogramme
        remplirChronogramme(tab1, tab2, tab3, tab4, listeProcessusPret, fileProcessusDisque, actifProcesseur, actifDisque, *i);

        // Print current time (for debugging or logging purposes)
        std::cout << "-------------------------------------------------------------------------------------" << *i << "\n";

        (*i)++;  // Increment time
    });

    timer->start(100);  // Exécute toutes les 250 ms
}


void PrioriteAvecRequisition::remplirChronogramme( QTableWidget* tab1 , QTableWidget* tab2 , QTableWidget* tab3 , QTableWidget* tab4 ,Liste listeP, File fileD, Processus *actifP, Processus *actifD , int col ){
    if(actifP){

        switch(actifP->getPid()){
        case 1 :
            tab1->setItem(0, col, new QTableWidgetItem("X"));
            break ;
        case 2 :
            tab2->setItem(0, col, new QTableWidgetItem("X"));
            break ;
        case 3 :
            tab3->setItem(0, col, new QTableWidgetItem("X"));
            break ;
        case 4 :
            tab4->setItem(0, col, new QTableWidgetItem("X"));
            break ;
        }

    }
    if(actifD){
        switch(actifD->getPid())
        {
        case 1 :
            tab1->setItem(2, col, new QTableWidgetItem("X"));
            break ;
        case 2 :
            tab2->setItem(2, col, new QTableWidgetItem("X"));
            break ;
        case 3 :
            tab3->setItem(2, col, new QTableWidgetItem("X"));
            break ;
        case 4 :
            tab4->setItem(2, col, new QTableWidgetItem("X"));
            break ;
        }
    }
    while(!listeP.est_vide()){
        Processus tete = listeP.prochain();

        switch(tete.getPid())
        {
        case 1 :
            tab1->setItem(1, col, new QTableWidgetItem("X"));
            break ;
        case 2 :
            tab2->setItem(1, col, new QTableWidgetItem("X"));
            break ;
        case 3 :
            tab3->setItem(1, col, new QTableWidgetItem("X"));
            break ;
        case 4 :
            tab4->setItem(1, col, new QTableWidgetItem("X"));
            break ;
        }


    }
    while(!fileD.est_vide()){
        Processus tete = fileD.tete() ;

        switch(tete.getPid()){
        case 1 :
            tab1->setItem(1, col, new QTableWidgetItem("X"));
            break ;
        case 2 :
            tab2->setItem(1, col, new QTableWidgetItem("X"));
            break ;
        case 3 :
            tab3->setItem(1, col, new QTableWidgetItem("X"));
            break ;
        case 4 :
            tab4->setItem(1, col, new QTableWidgetItem("X"));
            break ;
        }

        fileD.defiler() ;
    }
}



