#include <iostream>
#include <string>
#include <stdlib.h>
#include <ctime>

using namespace std;

class Disease
{
    //Membres
    int progression; //� 0 la maladie est vaincue, � 100 le Tamagotchi meurt
	bool vet; //faux � l'apparition de la maladie, vrai apr�s visite chez le v�to, le passer sur true permet de d�finir al�atoirement un intervalle
	int interval; //d�finit � quel rhytme doit �tre trait�e la maladie (exprim� en secondes)
	time_t lastHeal; //date du dernier soin

    //Fonctions
    public:
        Disease();
        Disease(int progression);
        int getProgression ();
        void setProgression (int progression);
        bool getVet ();
        void setVet (bool vet);
        void defineDiseaseRandomly();//(condition : vet==true) on d�finit al�atoirement un intervalle de soin (+ autres conditions apr�s si on a fini). Quand vet passe � false on supprime intervalle.
        int getInterval ();
        void setInterval (int interval);
        time_t getLastHeal ();
        void setLastHeal (time_t lastHeal);
        void setLastHeal (int lastHeal);
};
