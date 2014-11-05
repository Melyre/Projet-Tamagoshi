/*!
* \file Disease.h
* \brief Header de la classe Disease.
* \author Dupuy.N Roman.A Cartoux.T
*/

#include <iostream>
#include <string>
#include <stdlib.h>
#include <ctime>

using namespace std;

/*!
*	\class Disease
*	\brief Classe qui représente la maladie.
*
*	Cette classe représente une maladie du Tamagotchi ayant une progression, et un rythme de progression.
*/

class Disease
{
    int progression; /*! Etat de la maladie, à 0 la maladie est vaincue, à 100 le Tamagotchi meurt. */
	bool vet; /*! Variable qui définie si le Tamagotchi est allé diagnostiquer sa maladie chez le vétérnaire. Initialisée à false. */
	int interval; /*! Définie (en secondes) à quel rythme la maladie doit être traitée (toutes les 'interval' secondes). */
	time_t lastHeal; /*! Date à laquelle le dernier soin a été effectué. */

    public:
	
	/*!
	*	\brief Constructeur.
	*	
	*	Constructeur par défaut (sans arguments) de la classe Disease. Initialise la progression à 50 et la visite vétérinaire à false.
	*/
        Disease();
		
	/*!
	*	\brief Constructeur aavec arguments.
	*
	*	Constructeur avec arguments de la classe Disease. Permet d'initialiser la progression de la maladie à la valeur souhaitée.
	*
	*	\param progression : La progression de la maladie (en int) à initialiser. 
	*/
        Disease(int progression);
		
	/*!
	*	\brief Fonction get pour la progression.
	*
	*	\return La progression de la maladie.
	*/
        int getProgression ();
		
	/*!
	*	\brief Fonction set pour la progression.
	*
	*	\param progression : La progression de la maladie (en int) à changer .
	*/
        void setProgression (int progression);
		
	/*!
	*	\brief Fonction get pour la visite vétérinaire.
	*
	*	\return Retourne true si visite vétérinaire effectuée et false sinon.
	*/
        bool getVet ();
		
	/*!
	*	\brief Fonction set pour la visite vétérinaire.
	*
	*	\param vet : Le booléen qui définit si la visite vétérinaire a été effectuée.
	*/
        void setVet (bool vet);
		
	/*!
	*	\brief Intervalle aléatoire.
	*
	*	On définit l'intervalle entre les soins aléatoirement. L'intervalle sera entre 6 et 24 heures.
	*/
        void defineDiseaseRandomly();
        
	/*!
	*	\brief Fonction get pour l'intervalle.
	*
	*	\return L'intervalle entre les soins.
	*/	
		int getInterval ();
		
	/*!
	*	\brief Fonction set pour l'intervalle.
	*
	*	\param interval : L'intervalle (en int) entre les soins à changer.
	*/	
        void setInterval (int interval);
		
	/*!
	*	\brief Fonction get pour le dernier soin.
	*
	*	\return La date du dernier soin au format time_t.
	*/	
        time_t getLastHeal ();
		
	/*!
	*	\brief Fonction set pour le dernier soin.
	*
	*	\param lastHeal : La date (en time_t) du dernier soin à changer.
	*/	
        void setLastHeal (time_t lastHeal);
		
	/*!
	*	\brief Fonction set pour le dernier soin.
	*
	*	\param lastHeal : La date (en int) du dernier soin à changer.
	*/	
        void setLastHeal (int lastHeal);
};
