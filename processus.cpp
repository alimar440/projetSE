#include "processus.h"
unsigned int Processus::compteur = 0;

Processus::Processus(){
    pid = 0;

    dureeExecution = 0;
    dateArrivee = 0;

    tempsReponse = 0;
    tempsExecutionRestant = 0;
    tempsAttente = 0;
    priorite = 0;
    this->scenario = nullptr;

    elu = false;
    pret = false;
    bloque = false;
    entreeSortie = false;

    dateDernierEntreePret = 0;
}

Processus::Processus(unsigned int dureeExecution, double dateArrivee){

    pid = ++compteur;

    this->dureeExecution = dureeExecution;
    this->dateArrivee = dateArrivee;
    this->scenario = nullptr;

    tempsReponse = 0;
    tempsAttente = 0;
    tempsExecutionRestant = dureeExecution;
    priorite = 0;

    elu = false;
    pret = false;
    bloque = false;
    entreeSortie = false;

    dateDernierEntreePret = 0;
}

Processus& Processus::operator=(Processus& p2) {
    if (this == &p2) return *this;

    // Libération de la mémoire existante
    while (scenario != nullptr) {
        Scenario tmp = scenario->suivant;
        delete scenario;
        scenario = tmp;
    }

    // Copie des autres attributs
    pid = p2.pid;
    dureeExecution = p2.dureeExecution;
    dateArrivee = p2.dateArrivee;
    tempsReponse = p2.tempsReponse;
    tempsAttente = p2.tempsAttente;
    priorite = p2.priorite;
    tempsExecutionRestant = p2.tempsExecutionRestant;
    elu = p2.elu;
    pret = p2.pret;
    bloque = p2.bloque;
    entreeSortie = p2.entreeSortie;

    // Allocation mémoire pour scenario
    if (p2.scenario != nullptr) {
        scenario = new maillon;
        scenario->val = p2.scenario->val;
        scenario->type_operation = p2.scenario->type_operation;
        scenario->suivant = nullptr;

        Scenario tmp = p2.scenario->suivant;
        Scenario tmp2 = scenario;

        // Copie de la liste chainée
        while (tmp != nullptr) {
            tmp2->suivant = new maillon;
            tmp2 = tmp2->suivant;
            tmp2->val = tmp->val;
            tmp2->type_operation = tmp->type_operation;
            tmp2->suivant = nullptr;
            tmp = tmp->suivant;
        }
    } else {
        scenario = nullptr;
    }

    return *this;
}


void Processus::deplacer(){
    Scenario tmp = scenario;
    scenario = scenario->suivant;
    delete(tmp);
}

void Processus::ajouterScenario(int *tab, int taille)
{
    if(tab)
    {
        while(scenario){
            Scenario tmp = scenario;
            scenario = scenario->suivant;
            delete(tmp);
        }
        scenario= nullptr ;
        int vf = 0;
        int cmp = 0;
        int i = 0;
        while(i < taille && cmp < MAX)
        {
            Scenario tmp = new maillon;
            if(vf == 0)
            {
                tmp->type_operation = type::calcul;
                vf = 1;
            }
            else
            {
                tmp->type_operation = type::entreeSortie;
                vf = 0;
            }
            tmp->val = tab[i];
            tmp->suivant = scenario;
            scenario  = tmp;
            cmp += tab[i];
            i++;
        }
    }
}
void Processus::afficherScenario()
{
    Scenario tmp = scenario;
    while(tmp != nullptr)
    {
        tmp = tmp->suivant;
    }

}

