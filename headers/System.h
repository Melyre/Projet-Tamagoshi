#include <iostream>
#include <string>
#include "Tamagotchi.h"
#include "GUI.h"
#include "../includes/tinyxml/tinystr.h"
#include "../includes/tinyxml/tinyxml.h"

using namespace std;

class System
{
    //Membres
	Tamagotchi *pet;
	GUI *interface;
	string location;
	string saveName;
	int timeSpeed;
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
        void update (string lastTime);
        void saveGame ();
        void newGame ();
        void deleteSave ();
        void update ();
    };
