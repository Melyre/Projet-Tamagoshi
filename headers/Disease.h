#include <iostream>
#include <string>

using namespace std;

class Disease
{
    //Membres
    int progression; //� 0 la maladie est vaincue, � 100 le Tamagotchi meurt
	bool vet; //faux � l'apparition de la maladie, vrai apr�s visite chez le v�to, le passer sur true permet de d�finir al�atoirement un intervalle
	int interval; //d�finit � quel rhytme doit �tre trait�e la maladie
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
