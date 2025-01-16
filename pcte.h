#ifndef PCTE_H_INCLUDED
#define PCTE_H_INCLUDED

#define MAX 35
#define NB_PROCESS 4

#include <QTableWidget>
#include "file.h"
#include "liste.h"
#include "processus.h"

class Pcte{
private:
    Processus **tabProcessus;

    Liste listeProcessusPret;
    Processus *actifProcesseur;

    File fileProcessusDisque;
    Processus *actifDisque;


public:
    Pcte();

    ~Pcte();

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

    void executionPCTE(QTableWidget* tab1 , QTableWidget* tab2 , QTableWidget* tab3 , QTableWidget* tab4 ) ;

    void executionPCTE1(QTableWidget* tab1 , QTableWidget* tab2 , QTableWidget* tab3 , QTableWidget* tab4 ) ;

    Processus ** getTabProcess() { return tabProcessus ; } ;

};


#endif
