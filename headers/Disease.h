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
*	\brief Classe qui represente la maladie.
*
*	Cette classe represente une maladie du Tamagotchi ayant une progression, et un rythme de progression.
*/

class Disease
{
    int progression; /*! Etat de la maladie, a 0 la maladie est vaincue, a 100 le Tamagotchi meurt. */
	bool vet; /*! Variable qui definie si le Tamagotchi est alle diagnostiquer sa maladie chez le veternaire. Initialisee a false. */
	int interval; /*! Definie (en secondes) a quel rythme la maladie doit être traitee (toutes les 'interval' secondes). */
	time_t lastHeal; /*! Date a laquelle le dernier soin a ete effectue. */

    public:
	
	/*!
	*	\brief Constructeur.
	*	
	*	Constructeur par defaut (sans arguments) de la classe Disease. Initialise la progression a 50 et la visite veterinaire a false.
	*/
        Disease();
		
	/*!
	*	\brief Constructeur aavec arguments.
	*
	*	Constructeur avec arguments de la classe Disease. Permet d'initialiser la progression de la maladie a la valeur souhaitee.
	*
	*	\param progression : La progression de la maladie (en int) a initialiser. 
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
	*	\param progression : La progression de la maladie (en int) a changer .
	*/
        void setProgression (int progression);
		
	/*!
	*	\brief Fonction get pour la visite veterinaire.
	*
	*	\return Retourne true si visite veterinaire effectuee et false sinon.
	*/
        bool getVet ();
		
	/*!
	*	\brief Fonction set pour la visite veterinaire.
	*
	*	\param vet : Le booleen qui definit si la visite veterinaire a ete effectuee.
	*/
        void setVet (bool vet);
		
	/*!
	*	\brief Intervalle aleatoire.
	*
	*	On definit l'intervalle entre les soins aleatoirement. L'intervalle sera entre 6 et 24 heures.
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
	*	\param interval : L'intervalle (en int) entre les soins a changer.
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
	*	\param lastHeal : La date (en time_t) du dernier soin a changer.
	*/	
        void setLastHeal (time_t lastHeal);
		
	/*!
	*	\brief Fonction set pour le dernier soin.
	*
	*	\param lastHeal : La date (en int) du dernier soin a changer.
	*/	
        void setLastHeal (int lastHeal);
};
