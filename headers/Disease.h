#include <iostream>
#include <string>
#include <stdlib.h>
#include <ctime>

using namespace std;

class Disease
{
    //Membres
    int progression; //à 0 la maladie est vaincue, à 100 le Tamagotchi meurt
	bool vet; //faux à l'apparition de la maladie, vrai après visite chez le véto, le passer sur true permet de définir aléatoirement un intervalle
	int interval; //définit à quel rhytme doit être traitée la maladie (exprimé en secondes)
	time_t lastHeal; //date du dernier soin

    //Fonctions
    public:
        Disease();
        Disease(int progression);
        int getProgression ();
        void setProgression (int progression);
        bool getVet ();
        void setVet (bool vet);
        void defineDiseaseRandomly();//(condition : vet==true) on définit aléatoirement un intervalle de soin (+ autres conditions après si on a fini). Quand vet passe à false on supprime intervalle.
        int getInterval ();
        void setInterval (int interval);
        time_t getLastHeal ();
        void setLastHeal (time_t lastHeal);
        void setLastHeal (int lastHeal);
};
