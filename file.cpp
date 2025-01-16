#include "file.h"

File::File()
{
    tetef=queuef=nullptr;
}
File::~File()
{
    while(!est_vide())
    {
        defiler();
    }
}

void File::reset(){
    while(!est_vide()){
        defiler() ;
    }
    tetef=queuef=nullptr;
}
File::File(File& F2)
{
    tetef=queuef=nullptr;
    File F_tmp;
    while(!F2.est_vide())
    {
        enfiler(F2.tete());
        F_tmp.enfiler(F2.tete());
        F2.defiler();
    }
    while(!F_tmp.est_vide())
    {
        F2.enfiler(F_tmp.tete());
        F_tmp.defiler();
    }
}
File& File::operator=(File& F2)
{
    if(this==&F2) return *this;
    while(!est_vide())
    {
        defiler();
    }
    tetef=queuef=nullptr;
    File F_tmp;
    while(!F2.est_vide())
    {
        enfiler(F2.tete());
        F_tmp.enfiler(F2.tete());
        F2.defiler();
    }
    while(!F_tmp.est_vide())
    {
        F2.enfiler(F_tmp.tete());
        F_tmp.defiler();
    }
    return *this;
}

void File::enfiler(Processus e)
{
    Noeud *nouv=nullptr;
    nouv=new Noeud;
    nouv->element=e;
    nouv->suivant=nullptr;
    if(est_vide())
    {
        tetef=queuef=nouv;
    }
    else
    {
        queuef->suivant=nouv;
        queuef=nouv;
    }
}

Processus* File::defiler()
{
    Noeud *tmp=tetef;
    tetef=tetef->suivant;
    Processus *P = new Processus;
    *P = tmp->element;
    delete tmp;
    return P;
}

int File::est_vide()
{
    return tetef==nullptr;
}

Processus File::tete()
{
    return tetef->element;
}


