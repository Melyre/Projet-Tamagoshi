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
*	\brief Classe qui repr�sente la maladie.
*
*	Cette classe repr�sente une maladie du Tamagotchi ayant une progression, et un rythme de progression.
*/

class Disease
{
    int progression; /*! Etat de la maladie, � 0 la maladie est vaincue, � 100 le Tamagotchi meurt. */
	bool vet; /*! Variable qui d�finie si le Tamagotchi est all� diagnostiquer sa maladie chez le v�t�rnaire. Initialis�e � false. */
	int interval; /*! D�finie (en secondes) � quel rythme la maladie doit �tre trait�e (toutes les 'interval' secondes). */
	time_t lastHeal; /*! Date � laquelle le dernier soin a �t� effectu�. */

    public:
	
	/*!
	*	\brief Constructeur.
	*	
	*	Constructeur par d�faut (sans arguments) de la classe Disease. Initialise la progression � 50 et la visite v�t�rinaire � false.
	*/
        Disease();
		
	/*!
	*	\brief Constructeur aavec arguments.
	*
	*	Constructeur avec arguments de la classe Disease. Permet d'initialiser la progression de la maladie � la valeur souhait�e.
	*
	*	\param progression : La progression de la maladie (en int) � initialiser. 
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
	*	\param progression : La progression de la maladie (en int) � changer .
	*/
        void setProgression (int progression);
		
	/*!
	*	\brief Fonction get pour la visite v�t�rinaire.
	*
	*	\return Retourne true si visite v�t�rinaire effectu�e et false sinon.
	*/
        bool getVet ();
		
	/*!
	*	\brief Fonction set pour la visite v�t�rinaire.
	*
	*	\param vet : Le bool�en qui d�finit si la visite v�t�rinaire a �t� effectu�e.
	*/
        void setVet (bool vet);
		
	/*!
	*	\brief Intervalle al�atoire.
	*
	*	On d�finit l'intervalle entre les soins al�atoirement. L'intervalle sera entre 6 et 24 heures.
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
	*	\param interval : L'intervalle (en int) entre les soins � changer.
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
	*	\param lastHeal : La date (en time_t) du dernier soin � changer.
	*/	
        void setLastHeal (time_t lastHeal);
		
	/*!
	*	\brief Fonction set pour le dernier soin.
	*
	*	\param lastHeal : La date (en int) du dernier soin � changer.
	*/	
        void setLastHeal (int lastHeal);
};
