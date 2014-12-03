#ifndef GUI_H
#define GUI_H

#include <iostream>
#include <string>
#include <vector>

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

using namespace std;

//Constantes couleurs
const SDL_Color BLACK = {0, 0, 0};
const SDL_Color WHITE = {255, 255, 255};

struct Button
{
	SDL_Rect rect;
	string name;
};

class GUI
{
	//Pointeurs
	SDL_Cursor *ARROW;
	SDL_Cursor *POINTER;
	
    //Membres
    SDL_Surface *screen; //fenêtre du programme
	vector<Button> buttons;

    //Fonctions
    public:
        GUI();
        ~GUI();
        string waitEvent(); //retourne l'id de l'event reçu
        void clearButtons();
        void addButton(SDL_Rect button, string buttonName);
        string getButtonName(int x, int y);
        void switchCursor(SDL_Cursor *cursor);
        void displayMainMenu();
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


#endif
