#ifndef GUI_H
#define GUI_H

#include <iostream>
#include <string>
#include <vector>

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

using namespace std;

struct Button
{
	SDL_Rect rect;
	string name;
};

class GUI
{
	//Constantes couleurs
	static SDL_Color BLACK;
	static SDL_Color WHITE;
	
	//Pointeurs
	SDL_Cursor *ARROW;
	SDL_Cursor *POINTER;
	
    //Membres
    SDL_Window *window;
    SDL_Surface *screen;
	vector<Button> buttons;
	SDL_Surface *input;

    //Fonctions
    public:
        GUI();
        ~GUI();
        
        string waitEvent(); //retourne l'id de l'event reçu
        
        SDL_Rect centerPos(SDL_Surface *surface);
        void clearScreen();
        void clearButtons();
        void addButton(SDL_Rect button, string buttonName);
        string getButtonName(int x, int y);
        void switchCursor(SDL_Cursor *cursor);
        void updateInput(char *);
        
        void displayMainMenu();
        void displayNewGame(char *textInput);
        
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
