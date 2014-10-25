#include <iostream>
#include <string>

using namespace std;

class Disease
{
    //Membres
    int progression; //à 0 la maladie est vaincue, à 100 le Tamagotchi meurt
	bool vet; //faux à l'apparition de la maladie, vrai après visite chez le véto, le passer sur true permet de définir aléatoirement un intervalle
	int interval; //définit à quel rhytme doit être traitée la maladie
	int lastHeal;

    //Fonctions
    public:
        Disease();
        int getProgression ();
        void setProgression (int progression);
        bool getVet ();
        void setVet (bool vet);
        int getInterval ();
        void setInterval (int interval);
        int getLastHeal ();
        void setLastHeal (int lastHeal);

};
