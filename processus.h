#ifndef PROCESSUS_HPP_INCLUDED
#define PROCESSUS_HPP_INCLUDED

#define MAX 35

#include <iostream>

enum type{calcul, entreeSortie};

struct maillon{
    int val;
    type type_operation;
    struct maillon *suivant;
};

typedef struct maillon *Scenario;

class Processus{
private:
    unsigned int pid;
    unsigned int dureeExecution;
    double dateArrivee;
    double tempsReponse;
    double tempsAttente;
    double tempsExecutionRestant;
    unsigned int priorite;
    bool elu;
    bool pret;
    bool bloque;
    bool entreeSortie;
    Scenario scenario;

    unsigned int dateDernierEntreePret;
    static unsigned int compteur;//pour initialiser le PID du processus à sa création
public:
    Processus();
    Processus(unsigned int dureeExecution, double dateArrivee);
    Processus& operator=(Processus&);

    int getPid(){return pid;}
    int getDureeExecution(){return dureeExecution;}
    double getTempsReponse(){return tempsReponse;}
    double getDateArrivee(){ return dateArrivee;}
    double getTempsExecutionRestant(){ return tempsExecutionRestant;}
    double getTempsAttente(){return tempsAttente;}
    int getPriorite(){return priorite;}
    bool getElu(){ return elu;}
    bool getPret(){return pret;}
    bool getBloque(){return bloque;}
    bool getEntreeSortie(){return entreeSortie;}
    Scenario getScenario(){return scenario;}

    void setDureeExecution(unsigned int de ){dureeExecution = de;}
    void setTempsReponse(double tr){tempsReponse = tr;}
    void setDateArrivee(double da){ dateArrivee = da;}
    void setTempsAttente(double ta){tempsAttente = ta;}
    void setPriorite(unsigned int p){priorite = p;}
    void setElu(bool e){ elu = e;}
    void setPret(bool pr){pret = pr;}
    void setBloque(bool b){bloque = b;}
    void setEntreeSortie(bool es){entreeSortie = es;}
    void deplacer();

    void calculRestant(){
        tempsExecutionRestant--;
    };

    void calcul(){
        scenario->val--;
    };

    void ajouterScenario(int *tab, int taille);
    void afficherScenario();
};


#endif
