/*!
* \file GUI.h
* \brief Header de la classe GUI.
* \author Dupuy.N Roman.A Cartoux.T
*/

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

/*!
*	\class System
*	\brief Classe qui gere l'interface graphique du jeu.
*
*	Affiche les différents écrans de jeu et permet de récupérer les entrées utilisateurs.
*/

class GUI
{
	//Constantes couleurs
	static SDL_Color BLACK;
	static SDL_Color BLUE;
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
        
        string waitEvent(); //pause en attente d'un évènement et retourne le nom de l'event reçu
        
        /*!
		*	\brief Fonction d'attente d'événement avec limite de temps.
		*
		*	\param timeout : nombres de millisecondes durant lesquelles on attend un évènement
		*	\return Retourne une string contenant le nom de l'évènement reçu ou "timeout" si aucun élément n'a été reçu avant le temps limite.
		*/
        string waitEvent(int timeout);
        
        SDL_Rect centerPos(SDL_Surface *surface);
        void clearScreen(); //efface l'écran (en mémoire), à utiliser à chaque modification de l'affichage
        void clearButtons();
        void addButton(SDL_Rect button, string buttonName);
        string getButtonName(int x, int y);
        void switchCursor(SDL_Cursor *cursor);
        void updateInput(char *); //inutilisé, inutile ? on rappelle display avec un arguments char* à la place
        
        void displayMainMenu();
        void displayNewGame();
        void displayNewGameRace();
        void displayLoadGame();
        void displayGame(Tamagotchi *pet);
        void displayGauges(Tamagotchi *pet);
        int displayGauge(Tamagotchi *pet, int type, int topMarge);
        void displayDeleteGame();
        void displayDead();
        
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
