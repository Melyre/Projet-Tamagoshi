/*!
* \file Disease.h
* \brief Header de la classe System.
* \author Dupuy.N Roman.A Cartoux.T
*/

#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <stdio.h>
#include "GUI.h"
#include "../includes/tinyxml/tinystr.h"
#include "../includes/tinyxml/tinyxml.h"

using namespace std;

/*!
*	\class System
*	\brief Classe qui gere le deroulement du jeu.
*
*	Cette classe est le moteur du Tamagotchi, elle communique egalement avec toute la partie graphique.
*	Elle gere les evenements aleatoires, la communication utilisateur (menus, connexion a la partie graphique), le temps
*	(evolution des caracteristiques du Tamagotchi ainsi que la gestion des parties (creer, sauvegarder, supprimer etc ...).
*/

class System
{
	/*! Membres globaux parametres du jeu */

    const static float thirstDecay=1.33;//1h15 /*! Constante qui definit la perte de soif par minute
    const static float hungerDecay=1;//1h40
    const static float tirednessDecay=0.1;//16.6h
    const static float socialDecay=0.83;//2h
    const static float hygieneDecay=0.4;//4h10
    const static float businessDecay=0.9;//1h50

    //Membres
	Tamagotchi *pet;	/*! Pointeur vers la Tamagotchi que le systeme fait tourner (voir classe Tamagotchi) */
	GUI *interface;		/*! Pointeur vers l'interface (voir classe GUI) */
	string location;	/*! String definissant la localisation du Tamagotchi (dehors, au parc, dedans etc ... ) */
	string saveName;	/*! Nom de la sauvegarde chargee dans le systeme. */
	float timeSpeed;	/*! Vitesse a laquelle s'ecoule le temps dans le jeu. */
	string weather;		/*! Temps qu'il fait dans le jeu. */
	bool endGame;		/*! Variable qui previent la fonction rungame que le jeu doit s'interrompre (retour menu). */
	bool endProgram;	/*! Variable qui previent la fonction principale que le programme doit s'interrompre. */

    //Fonctions
    public:

	/*!
	*	\brief Constructeur
	*
	*	La constructeur de la classe systeme.
	*/
        System();

	/*!
	*	\brief Constructeur avec arguments
	*
	*	Constructeur de la classe systeme a partie d'un fichier de configuration.
	*/
        System(string configFile);


	//Accesseurs

	/*!
	*	\brief Fonction get pour la meteo.
	*
	*	\return Un string indiquant la meteo.
	*/
        string getWeather ();

	/*!
	*	\brief Fonction get pour la localisation du Tamagotchi.
	*
	*	\return Un string indiquant un lieu (dehors, dedans, au parc, au veterinaire ... ).
	*/
        string getLocation ();

	/*!
	*	\brief Fonction get pour le Tamagotchi.
	*
	*	\return Un pointeur vers le Tamagotchi en cours de partie.
	*/
        Tamagotchi * getPet ();

	/*!
	*	\brief Fonction set pour finir le programme (endProgram).
	*
	*	\param end : booleen true pour finir le programme false sinon.
	*/
        void setEndProgram (bool end);

	/*!
	*	\brief Fonction set pour finir la partie (endGame).
	*
	*	\param end : booleen true pour finir la partie false sinon.
	*/
        void setEndGame (bool end);

	/*!
	*	\brief Menu principal
	*
	*	Cette fonction appelle l'affichage du menu principal (voir classe GUI) et gere les fonctionalites de ce menu. Le jeu doit être lancé avec cette fonction.
	*/
        void mainMenu ();


    private:

    //Gestion des sauvegardes

	/*!
	*	\brief Fonction qui sauvegarde les donnees de la partie en XML.
	*/
        bool saveGame ();

	/*!
	*	\brief Fonction qui lance une nouvelle partie (nouveau Tamagotchi).
	*
	*	\return False si il y a une erreur, true sinon.
	*/
        bool newGame (string petName);

	/*!
	*	\brief Fonction qui supprime une sauvegarde XML.
	*
	*	\param petName : chaîne de caractère contenant le nom du Tamagotchi (et pas le nom de la sauvegarde).
	*	\return False si il y a une erreur, true sinon.
	*/
        bool deleteSave ();

	/*!
	*	\brief Fonction chargement d'un jeu.
	*/
        void loadGame ();

	/*!
	*	\brief Fonction chargement d'un jeu a partir d'une sauvegarde XML.
	*
	*	\return False si impossible de charger la sauvegarde, true sinon.
	*/
        bool loadGame(string saveFile);
        
	/*!
	*	\brief Fonction supprimant une partie.
	*
	* 	\return False si impossible de supprimer la sauvegarde, true sinon.
	*/
        bool deleteGame(string saveFile);


    //Ecrans, menus

	/*!
	*	\brief Menu d'options
	*
	*	Cette fonction appelle l'affichage du menu options (voir classe GUI) et gere les fonctionalites de ce menu.
	*/
        void optionMenu ();

   	/*!
	*	\brief Menu de création d'une nouvelle partie
	*
	*	Cette fonction appelle l'affichage du menu Nouvelle partie (voir classe GUI) et gere les fonctionalites de ce menu.
	*/
        void newGameMenu ();

   	/*!
	*	\brief Menu de chargement d'une partie
	*
	*	Cette fonction appelle l'affichage du menu Charger partie (voir classe GUI) et gere les fonctionalites de ce menu.
	*/
        void loadGameMenu ();
        
    /*!
	*	\brief Menu de Suppression d'une partie
	*
	*	Cette fonction appelle l'affichage du menu Supprimer partie (voir classe GUI) et gere les fonctionalites de ce menu.
	*/
        void deleteGameMenu ();

	/*!
	*	\brief Fonction qui fait tourner la partie.
	*/
        void runGame ();

	/*!
	*	\brief Fonction qui actualise tout le Tamagotchi au chargement.
	*
	*	\param lastTime : Correspond a la derniere fois que le programme a ete execute.
	*	\return False si lastTime est incorrect, true sinon.
	*/


	//Fonctions de mise à jour
        bool update (const time_t &lastTime);

	/*!
	*	\brief Fonction qui update tres regulierement les donnees du Tamagotchi (changement des jauges et etats) en fonction du temps ecoule.
	*/
        void update ();


	//Actions du joueur

	/*!
	*	\brief Fonction pour nourir le Tamagotchi.
	*
	*	\param n : definit de combien on nourrit le Tamagotchi.
	*/
        void feed (int n);

	/*!
	*	\brief Fonction pour donner a boire au Tamagotchi.
	*
	*	\param n : definit de combien on hydrate le Tamagotchi.
	*/
        void giveDrink (int n);

    /*!
	*	\brief Fonction pour laisser faire ses besoins au Tamagotchi.
	*/
        void doBusiness ();

	/*!
	*	\brief Fonction pour reveiller le Tamagotchi.
	*
	*	Le Tamagotchi dort pendant la nuit et le joueur peut quand même le reveiller pour jouer.
	*/
        void wakeUp ();

	/*!
	*	\brief Fonction pour soigner la maladie du Tamagotchi.
	*
	*	\param n : definit de combien on baisse la progression de la maladie (Disease).
	*/
        void heal (int n);

	/*!
	*	\brief Fonction pour laver le Tamagotchi.
	*
	*	\param n : definit de combien on baisse la jauge d'hygiene.
	*/
        void wash (int n);

	/*!
	*	\brief Fonction pour jouer avec le Tamagotchi.
	*
	*	\param n : definit de combien on baisse la jauge sociale.
	*/
        void play (int n);

	/*!
	*	\brief Fonction pour lancer un mini-jeu.
	*/
        void playMini ();

	/*!
	*	\brief Fonction pour sortir.
	*
	*	Fonction qui fait sortir le Tamagotchi au parc, au veterinaire etc ... Change la ' location '.
	*/
        void goOut ();

    };
