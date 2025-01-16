#ifndef FILE_HPP_INCLUDED
#define FILE_HPP_INCLUDED

#include "processus.h"

#include <iostream>

struct Noeud
{
    Processus element;
    Noeud *suivant;
};

class File
{
private:
    Noeud *tetef;
    Noeud *queuef;
public:
    File();
    ~File();
    File(File&);
    File& operator=(File&);
    void enfiler(Processus);
    Processus* defiler();
    Processus tete();
    int est_vide();
    friend void afficher(File);
    void reset() ;

};



#endif
