#include "liste.h"

Liste::Liste(){
    liste = nullptr;
}

void Liste::ajouter(Processus* p){

    if(est_vide())
    {
        liste = new struct Maillon;
        liste->element = *p;
        liste->suivant = nullptr;

    }
    else
    {
        noeud m =  new struct Maillon;
        m->element = *p;
        m->suivant = liste;
        liste = m;
    }
}

Processus* Liste::prochainPCTE(){
    Processus *Pmin = new Processus;
    if(liste != nullptr)
    {
        if(liste->suivant == nullptr){
            *Pmin = liste->element;
            delete(liste);
            liste = nullptr;
            return Pmin;
        }

        noeud pre = liste, cour = liste->suivant, suiv = liste->suivant->suivant;

        *Pmin = liste->element;
        int vf = 0;
        if(Pmin->getDureeExecution() > cour->element.getDureeExecution()){
            *Pmin = cour->element;
            vf = 1;
        }

        while(suiv)
        {
            if(Pmin->getDureeExecution() > suiv->element.getDureeExecution()){
                *Pmin = suiv->element;
                pre = cour;
            }
            cour = cour->suivant;
            suiv = suiv->suivant;
        }
        if(pre == liste)
        {
            if(vf == 0)
            {
                noeud tmp = liste;
                liste = liste->suivant;
                delete(tmp);
            }
            else
            {
                noeud tmp = pre->suivant;
                pre->suivant = pre->suivant->suivant;
                delete(tmp);
            }
        }
        else
        {
            noeud tmp = pre->suivant;
            pre->suivant = pre->suivant->suivant;
            delete(tmp);
        }
        return Pmin;
    }
    return nullptr;
}


Processus* Liste::prochainPriorite(){
    Processus *Pmin = new Processus;
    if(liste != nullptr)
    {
        if(liste->suivant == nullptr){
            *Pmin = liste->element;
            delete(liste);
            liste = nullptr;
            return Pmin;
        }

        noeud pre = liste, cour = liste->suivant, suiv = liste->suivant->suivant;

        *Pmin = liste->element;
        int vf = 0;
        if(Pmin->getPriorite() < cour->element.getPriorite()){
            *Pmin = cour->element;
            vf = 1;
        }

        while(suiv)
        {
            if(Pmin->getPriorite() < suiv->element.getPriorite()){
                *Pmin = suiv->element;
                pre = cour;
            }
            cour = cour->suivant;
            suiv = suiv->suivant;
        }
        if(pre == liste)
        {
            if(vf == 0)
            {
                noeud tmp = liste;
                liste = liste->suivant;
                delete(tmp);
            }
            else
            {
                noeud tmp = pre->suivant;
                pre->suivant = pre->suivant->suivant;
                delete(tmp);
            }
        }
        else
        {
            noeud tmp = pre->suivant;
            pre->suivant = pre->suivant->suivant;
            delete(tmp);
        }
        return Pmin;
    }
    return nullptr;
}

Processus Liste::prochain(){
    Processus temp ;
    temp = liste->element ;
    liste = liste->suivant ;
    return temp ;
}

bool Liste::est_vide(){
    return liste == nullptr;
}




Processus* Liste::prochainPCTER(){
    Processus *Pmin = new Processus;
    if(liste != NULL)
    {
        if(liste->suivant == nullptr){
            *Pmin = liste->element;
            delete(liste);
            liste = nullptr;
            return Pmin;
        }

        noeud pre = liste, cour = liste->suivant, suiv = liste->suivant->suivant;

        *Pmin = liste->element;
        int vf = 0;
        if(Pmin->getTempsExecutionRestant() > cour->element.getTempsExecutionRestant()){
            *Pmin = cour->element;
            vf = 1;
        }

        while(suiv)
        {
            if(Pmin->getTempsExecutionRestant() > suiv->element.getTempsExecutionRestant()){
                *Pmin = suiv->element;
                pre = cour;
            }
            cour = cour->suivant;
            suiv = suiv->suivant;
        }
        if(pre == liste)
        {
            if(vf == 0)
            {
                noeud tmp = liste;
                liste = liste->suivant;
                delete(tmp);
            }
            else
            {
                noeud tmp = pre->suivant;
                pre->suivant = pre->suivant->suivant;
                delete(tmp);
            }
        }
        else
        {
            noeud tmp = pre->suivant;
            pre->suivant = pre->suivant->suivant;
            delete(tmp);
        }
        return Pmin;
    }
    return nullptr;
}
