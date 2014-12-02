#ifndef GUI_H
#define GUI_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Tamagotchi.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"

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
	static SDL_Color LIGHTGREY;
	
	//Pointeurs
	SDL_Cursor *ARROW;
	SDL_Cursor *POINTER;
	
    //Membres
    SDL_Window *window;
    SDL_Surface *screen;
	vector<Button> buttons;
	SDL_Surface *input;
	char textInput[32]; //on stocke les saisies en mémoire 

    //Fonctions
    public:
        GUI();
        ~GUI();
        
        void getTextInput(string &dest);
        
        string waitEvent(); //retourne l'id de l'event reçu
        
        SDL_Rect centerPos(SDL_Surface *surface);
        void clearScreen(); //efface l'écran (en mémoire), à utiliser à chaque modification de l'affichage
        void clearButtons();
        void addButton(SDL_Rect button, string buttonName);
        string getButtonName(int x, int y);
        void switchCursor(SDL_Cursor *cursor);
        void updateInput(char *); //inutilisé, inutile ? on rappelle display avec un arguments char* à la place
        
        void displayMainMenu();
        void displayNewGame();
        void displayLoadGame();
        void displayGame(Tamagotchi *pet);
        void displayGauges(Tamagotchi *pet);
        int displayGauge(Tamagotchi *pet, int type, int topMarge);
        void displayDeleteGame();
        
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
