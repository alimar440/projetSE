#ifndef TOURNIQUET_H_INCLUDED
#define TOURNIQUET_H_INCLUDED



//#define QUANTUM 2
#define MAX 35
#define NB_PROCESSUS 4

#include <QTableWidget>

#include "file.h"
#include "processus.h"

class Tourniquet{
private:

    Processus **tabProcessus;

    File fileProcessusPret;
    Processus *actifProcesseur;

    File fileProcessusDisque;
    Processus *actifDisque;

    int compteur;


public:
    Tourniquet();

    ~Tourniquet();

    void ajouterProcessus(Processus*);

    int choix();

    void enfilerVersProcesseur(Processus);

    void enfilerVersDisque(Processus);

    Processus defilerFromProcesseur();

    Processus defilerFromDisque();

    void misAJourElu(File *F, File *F2, Processus* actif1, Processus* actif2, int sens , int QUANTUM );



    void executionTourniquet();

    void remplirChronogramme(QTableWidget* tab1 , QTableWidget* tab2 , QTableWidget* tab3 , QTableWidget* tab4 ,
                             File file1, File file2, Processus *process1, Processus *process2, int time);

    void executionTourniquet(QTableWidget* tab1 , QTableWidget* tab2 , QTableWidget* tab3 , QTableWidget* tab4 , int qt ) ;

    void executionTourniquet1(QTableWidget* tab1 , QTableWidget* tab2 , QTableWidget* tab3 , QTableWidget* tab4 , int qt) ;

    Processus ** getTabProcess() { return tabProcessus ; } ;

};


#endif
