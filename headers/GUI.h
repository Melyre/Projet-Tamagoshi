#include <iostream>
#include <string>
#include <vector>

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

using namespace std;

struct Button
{
	SDL_Rect rect;
	string name;
};

class GUI
{
    //Membres
	vector<Button> buttons; 

    //Fonctions
    public:
        GUI();
        ~GUI();
        string waitEvent(); //retourne l'id de l'event reçu
        void clearButtons();
        void addButton(SDL_Rect button, string buttonName);
        string getButtonName(int x, int y);
        void updateAll();
        void updateLocation();
        void updateThirst();
        void updateHunger();
        void updateTiredness();
        void updateSocial();
        void updateHygiene();
        void updateBusiness();
        void updateMood();
        void updateAffection();
        void updateDisease();
};
