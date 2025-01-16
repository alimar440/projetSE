#ifndef LISTE_H_INCLUDED
#define LISTE_H_INCLUDED

#include "processus.h"

struct Maillon{
    Processus element;
    struct Maillon* suivant;
};

typedef struct Maillon* noeud;

class Liste{

private:
    noeud liste;

public:
    Liste();


    void ajouter(Processus*);
    Processus* prochainPCTE();
    Processus* prochainPCTER();
    Processus* prochainPriorite();
    bool est_vide();
    Processus prochain() ;

};

#endif
