#include <iostream>
#include <string>
#include "Disease.h"

using namespace std;

class Tamagotchi
{
    //Membres statiques
    static const int MAX_GAUGE_VALUE=100;

    //Membres
    string race;
	string name;
	float thirst;
	float hunger;
	float tiredness;
	float social;
	float hygiene;
	float business;
	float mood;
	float affection;
	int life;
	Disease *disease;
	bool sleep;

    //Fonctions
    public:
        Tamagotchi();
        ~Tamagotchi();
        Tamagotchi(string race);
        Tamagotchi(string race, string name);
        string getRace ();
        void setRace (string race);
        string getName ();
        void setName (string name);
        float getThirst ();
        void setThirst (float thirst);
        float getHunger ();
        void setHunger (float hunger);
        float getTiredness ();
        void setTiredness (float tiredness);
        float getSocial ();
        void setSocial (float social);
        float getHygiene ();
        void setHygiene (float hygiene);
        float getBusiness ();
        void setBusiness (float business);
        float getMood ();
        void setMood (float mood);
        float getAffection ();
        void setAffection (float affection);
        Disease * getDisease();
        void setDisease (Disease *disease);
        bool getSleep ();
        void setSleep (bool sleep);
        int getLife();
        void setLife(int life);
};
