#ifndef FIFO_H_INCLUDED
#define FIFO_H_INCLUDED


#define NB_PROCESSUS 4
// #include <iostream>

#include "file.h"
#include "processus.h"
#include <QTableWidget>


class Fifo{
private:
    Processus **tabProcessus;

    File fileProcessusPret;
    Processus *actifProcesseur;

    File fileProcessusDisque;
    Processus *actifDisque;

    File fileT ;


public:
    Fifo();

    ~Fifo();




    void ajouterProcessus(Processus*);

    int choix();

    void enfilerVersProcesseur(Processus);

    void enfilerVersDisque(Processus);

    Processus defilerFromProcesseur();

    Processus defilerFromDisque();

    void misAJourElu(File *F, File *F2, Processus* actif1, Processus* actif2, int sens);

    void executionFIFO(QTableWidget* tab1 , QTableWidget* tab2 , QTableWidget* tab3 , QTableWidget* tab4 ,int lieu);

    void remplirChronogramme(QTableWidget* tab1 , QTableWidget* tab2 , QTableWidget* tab3 , QTableWidget* tab4 ,
                             File file1, File file2, Processus *process1, Processus *process2, int time);

    void tempsFIFO( QTableWidget* tab ,  Processus **tabProcessus ) ;

    void tempsFIFO0( QTableWidget* tab ) ;

    Processus ** getTabProcess() { return tabProcessus ; } ;
};


#endif
