#ifndef PRIORITE_AVEC_REQUISITION_H_INCLUDED
#define PRIORITE_AVEC_REQUISITION_H_INCLUDED

#define MAX 35
#define NB_PROCESSUS 4

#include "file.h"
#include "liste.h"
#include "processus.h"
#include <QTableWidget>
class PrioriteAvecRequisition{
private:
    Processus **tabProcessus;

    Liste listeProcessusPret;
    Processus *actifProcesseur;

    File fileProcessusDisque;
    Processus *actifDisque;


public:
    PrioriteAvecRequisition();

    ~PrioriteAvecRequisition();

    void ajouterProcessus(Processus*);

    int choix();

    void enfilerVersProcesseur(Processus);

    void enfilerVersDisque(Processus);

    Processus defilerFromProcesseur();

    Processus defilerFromDisque();

    void misAJourElu(Liste *L, File *F, Processus* actif1, Processus* actif2);

    void misAJourCoteDisque(File *F, Liste *L, Processus* actif1, Processus* actif2);

    void remplirChronogramme(QTableWidget* tab1 , QTableWidget* tab2 , QTableWidget* tab3 , QTableWidget* tab4 ,
                             Liste listeP, File file2, Processus *process1, Processus *process2, int time);

    void executionPrioriteAvecRequisition1(QTableWidget* tab1 , QTableWidget* tab2 , QTableWidget* tab3 , QTableWidget* tab4 ) ;

    void executionPrioriteAvecRequisition(QTableWidget* tab1 , QTableWidget* tab2 , QTableWidget* tab3 , QTableWidget* tab4 ) ;
    Processus ** getTabProcess() { return tabProcessus ; } ;

};


#endif
