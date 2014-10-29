#include <iostream>
#include <string>
#include <ctime>
#include "Tamagotchi.h"
#include "GUI.h"
#include "../includes/tinyxml/tinystr.h"
#include "../includes/tinyxml/tinyxml.h"

using namespace std;

class System
{
    //Membres globaux (paramètres du jeu)
    //_Decay => perte / minute des stats du pet
    const static float thirstDecay=1.33;//1h15
    const static float hungerDecay=1;//1h40
    const static float tirednessDecay=0.1;//16.6h
    const static float socialDecay=0.83;//2h
    const static float hygieneDecay=0.4;//4h10
    const static float businessDecay=0.9;//1h50

    //Membres
	Tamagotchi *pet;
	GUI *interface;
	string location;
	string saveName;
	float timeSpeed;
	string weather;
	bool endGame;
	bool endProgram;

    //Fonctions
    public:
        System();
        System(string configFile);
        void mainMenu ();
        void optionMenu ();
        void backToMenu ();
        string getWeather ( );
        string getLocation ();
        Tamagotchi * getPet ();
        void setEndProgram (bool end);
        void setEndGame (bool end);
        void feed (int n);
        void giveDrink (int n);
        void wakeUp ( );
        void heal (int n);
        void wash (int n);
        void playMini ( );
        void goOut ();
        void doBusiness (int n);
    private:
        void loadGame ();
        bool loadGame(string saveFile);
        void runGame ();
        bool update (const time_t &lastTime);
        bool saveGame ();
        void newGame ();
        void deleteSave ();
        void update ();
    };
