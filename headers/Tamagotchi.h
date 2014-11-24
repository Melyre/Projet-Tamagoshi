#include <iostream>
#include <string>
#include "Disease.h"

using namespace std;

class Tamagotchi
{
    //Membres
    string race;
	string name;
	int thirst;
	int hunger;
	int tiredness;
	int social;
	int hygiene;
	int business;
	int mood;
	int affection;
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
        int getThirst ();
        void setThirst (int thirst);
        int getHunger ();
        void setHunger (int hunger);
        int getTiredness ();
        void setTiredness (int tiredness);
        int getSocial ();
        void setSocial (int social);
        int getHygiene ();
        void setHygiene (int hygiene);
        int getBusiness ();
        void setBusiness (int business);
        int getMood ();
        void setMood (int mood);
        int getAffection ();
        void setAffection (int affection);
        Disease * getDisease();
        void setDisease (Disease *disease);
        bool getSleep ();
        void setSleep (bool sleep);
        int getLife();
        void setLife(int life);
};
