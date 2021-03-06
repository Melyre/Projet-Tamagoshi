#include "../headers/System.h"

using namespace std;

System::System()
{
	interface=new GUI();

	//informations sur la partie d�finies au chargement
    pet=NULL; //l'instanciation se fait au chargement de partie
    location="undefined";
    weather="undefined";
    timeSpeed=1.0;

    endGame=false;
    endProgram=false;
}

bool System::update(const time_t &lastTime)
{
	time_t currentTime=time(NULL);
    float elapsedTime=difftime(currentTime,lastTime); //Calcul du temps ecoule depuis la derniere sauvegarde
    cout<<"System (update) > Temps ecoule : "<<elapsedTime<<" secondes."<<endl;

    if(elapsedTime<0)//si la sauvegarde est posterieure a la date actuelle (travel time!)
    {
        cerr<<"System (update) > Erreur: La date de derniere sauvegarde est plus recente que la date actuelle("<<elapsedTime<<"), la sauvegarde a peut-�tre ete corrompue ou le systeme n'est pas a l'heure."<<endl;
        cerr<<"System (update) > Impossible de mettre a jour les donnees de la partie !"<<endl;
        return false;
    }

    if(elapsedTime>0)//comme �a si elapsedTime==0 on ne fait rien (ne devrait pas arriver)
    {
        elapsedTime/=60;//conversion en minutes
        pet->setThirst( pet->getThirst() + thirstDecay*elapsedTime );
        pet->setHunger( pet->getHunger() + hungerDecay*elapsedTime );
        pet->setSocial( pet->getSocial() + socialDecay*elapsedTime );
        pet->setHygiene( pet->getHygiene() + hygieneDecay*elapsedTime );
        pet->setBusiness( pet->getBusiness() + businessDecay*elapsedTime );
        
        //Fatigue, sommeil
        if(!pet->getSleep()) //si le Tamagotchi ne dormait pas avant la sauvegarde
        {
        	float missingTiredness = 100 - pet->getTiredness();
        	float tirednessIncrease = tirednessDecay * elapsedTime;
        	if(tirednessIncrease < missingTiredness)
        	{
        		pet->setTiredness( pet->getTiredness() + tirednessIncrease );
        	}
        	else
        	{
        		tirednessIncrease -= missingTiredness;
        		pet->setTiredness(100 - tirednessIncrease);
        		if(pet->getTiredness()>0) pet->setSleep(true);
        	}
        }
        
        else //si le Tamagotchi dormait pas avant la sauvegarde
        {
        	float tirednessDecrease = tirednessDecay * elapsedTime;
        	if(tirednessDecrease < pet->getTiredness())
        	{
        		pet->setTiredness( pet->getTiredness() - tirednessDecrease );
        	}
        	else
        	{
        		tirednessDecrease -= pet->getTiredness();
        		pet->setTiredness(0 + tirednessDecrease);
        		if(pet->getTiredness()<100) pet->setSleep(false);
        	}
        }
        
        int m=0;
        if (pet->getThirst() >= 90) { m++; }
        if (pet->getHunger() >= 90) { m++; }
        if (pet->getTiredness() >= 90) { m++; }
        if (pet->getHygiene() >= 90) { m++; }
        if (pet->getBusiness() >= 90) { m++; }
        if (pet->getThirst() >= 80) { m++; }
        if (pet->getHunger() >= 80) { m++; }
        if (pet->getTiredness() >= 80) { m++; }
        if (pet->getHygiene() >= 80) { m++; }
        if (pet->getBusiness() >= 80) { m++; }
        if (pet->getThirst() >= 70) { m++; }
        if (pet->getHunger() >= 70) { m++; }
        if (pet->getTiredness() >= 70) { m++; }
        if (pet->getHygiene() >= 70) { m++; }
        if (pet->getBusiness() >= 70) { m++; }
        if (m != 0) { pet->setLife(pet->getLife()-((elapsedTime*60.0)*(m*(5.0/(60.0*60.0))))); }
        else { pet->setLife(pet->getLife()+((elapsedTime*60.0)*(5.0/(60.0*60.0)))); }
        
        if (pet->getDisease() == NULL)
		{
			srand( time (NULL) );
			int dis=rand()%1000000;
			if (dis == 577025)
			{
				float progression=rand()%51;
				Disease *D=new Disease(progression);
				pet->setDisease(D);
			}
		}
		else if (pet->getDisease()->getProgression() < 100.0)
		{
			if (pet->getDisease()->getVet() == false) {  pet->getDisease()->setProgression(pet->getDisease()->getProgression()+((elapsedTime*60.0)*(20.0/(60.0*60.0)))); }
			else
			{
				float healTime=difftime(pet->getDisease()->getLastHeal(),lastUpdate);
				if (healTime < pet->getDisease()->getInterval())
				{
					pet->getDisease()->setProgression(pet->getDisease()->getProgression()-(healTime*(20.0/(60.0*60.0))));
				}
				else
				{
					pet->getDisease()->setProgression(pet->getDisease()->getProgression()-(pet->getDisease()->getInterval()*(20.0/(60.0*60.0))));
					pet->getDisease()->setProgression(pet->getDisease()->getProgression()+((elapsedTime*60.0)*(20.0/(60.0*60.0))));
				}
			}
			if (pet->getDisease()->getProgression() >= 100.0) { pet->setLife(-500.0); }
			if (pet->getDisease()->getProgression() <= 0.0) { delete  pet->getDisease(); pet->setDisease(NULL); }
		}
        
    }
    
    lastUpdate=currentTime;
    return true;
}

bool System::update()
{
	time_t currentTime=time(NULL);
    float elapsedTime=difftime(currentTime,lastUpdate); //Calcul du temps ecoule depuis la derniere sauvegarde
    cout<<"System (update) > Temps ecoule : "<<elapsedTime<<" secondes."<<endl;

    if(elapsedTime<0)//si la date est posterieure � la date actuelle (travel time!)
    {
        cerr<<"System (update) > Erreur: La date de derniere mise a jour est plus recente que la date actuelle("<<elapsedTime<<"), le systeme n'est peut-etre pas a l'heure."<<endl;
        cerr<<"System (update) > Impossible de mettre a jour les donnees de la partie !"<<endl;
        return false;
    }

    if(elapsedTime>0)//comme �a si elapsedTime==0 on ne fait rien (ne devrait pas arriver)
    {
        elapsedTime/=60;//conversion en minutes
        
        //Mise � jour des stats du Tamagotchi
        pet->setThirst( pet->getThirst() + thirstDecay*elapsedTime );
        pet->setHunger( pet->getHunger() + hungerDecay*elapsedTime );
        pet->setSocial( pet->getSocial() + socialDecay*elapsedTime );
        pet->setHygiene( pet->getHygiene() + hygieneDecay*elapsedTime );
        pet->setBusiness( pet->getBusiness() + businessDecay*elapsedTime );
        
         //Fatigue, sommeil
        if(!pet->getSleep()) //si le Tamagotchi ne dormait pas avant le dernier update
        {
        	float missingTiredness = 100 - pet->getTiredness();
        	float tirednessIncrease = tirednessDecay * elapsedTime;
        	if(tirednessIncrease < missingTiredness)
        	{
        		pet->setTiredness( pet->getTiredness() + tirednessIncrease );
        	}
        	else
        	{
        		tirednessIncrease -= missingTiredness;
        		pet->setTiredness(100 - tirednessIncrease);
        		if(pet->getTiredness()>0) pet->setSleep(true);
        	}
        }
        
        else //si il dormait
        {
        	float tirednessDecrease = tirednessDecay * elapsedTime;
        	if(tirednessDecrease < pet->getTiredness())
        	{
        		pet->setTiredness( pet->getTiredness() - tirednessDecrease );
        	}
        	else
        	{
        		tirednessDecrease -= pet->getTiredness();
        		pet->setTiredness(0 + tirednessDecrease);
        		if(pet->getTiredness()<100) pet->setSleep(false);
        	}
        }
        
        int m=0;
        if (pet->getThirst() >= 90) { m++; }
        if (pet->getHunger() >= 90) { m++; }
        if (pet->getTiredness() >= 90) { m++; }
        if (pet->getHygiene() >= 90) { m++; }
        if (pet->getBusiness() >= 90) { m++; }
        if (pet->getThirst() >= 80) { m++; }
        if (pet->getHunger() >= 80) { m++; }
        if (pet->getTiredness() >= 80) { m++; }
        if (pet->getHygiene() >= 80) { m++; }
        if (pet->getBusiness() >= 80) { m++; }
        if (pet->getThirst() >= 70) { m++; }
        if (pet->getHunger() >= 70) { m++; }
        if (pet->getTiredness() >= 70) { m++; }
        if (pet->getHygiene() >= 70) { m++; }
        if (pet->getBusiness() >= 70) { m++; }
        if (m != 0) { pet->setLife(pet->getLife()-((elapsedTime*60.0)*(m*(5.0/(60.0*60.0))))); }
        else { pet->setLife(pet->getLife()+((elapsedTime*60.0)*(5.0/(60.0*60.0)))); }
        
		if (pet->getDisease() == NULL)
		{
			srand( time (NULL) );
			int dis=rand()%1000000;
			if (dis == 577025)
			{
				float progression=rand()%51;
				Disease *D=new Disease(progression);
				pet->setDisease(D);
			}
		}
		else if (pet->getDisease()->getProgression() < 100.0)
		{
			if (pet->getDisease()->getVet() == false) {  pet->getDisease()->setProgression(pet->getDisease()->getProgression()+((elapsedTime*60.0)*(20.0/(60.0*60.0)))); }
			else
			{
				float healTime=difftime(pet->getDisease()->getLastHeal(),lastUpdate);
				if (healTime < pet->getDisease()->getInterval())
				{
					pet->getDisease()->setProgression(pet->getDisease()->getProgression()-(healTime*(20.0/(60.0*60.0))));
				}
				else
				{
					pet->getDisease()->setProgression(pet->getDisease()->getProgression()-(pet->getDisease()->getInterval()*(20.0/(60.0*60.0))));
					pet->getDisease()->setProgression(pet->getDisease()->getProgression()+((elapsedTime*60.0)*(20.0/(60.0*60.0))));
				}
			}
			if (pet->getDisease()->getProgression() >= 100.0) { pet->setLife(-500.0); }
			if (pet->getDisease()->getProgression() <= 0.0) { delete  pet->getDisease(); pet->setDisease(NULL); }
		}
        
    }
    
    lastUpdate=currentTime;
    return true;
}


/***************************************
********* GESTION SAUVEGARDES **********
****************************************/

bool System::newGame(string petName, string petRace)
{
    TiXmlDocument saveDoc;

    TiXmlDeclaration *declaration=new TiXmlDeclaration("1.0","UTF-8","yes");
    saveDoc.LinkEndChild(declaration);//on ajoute la declaration a la fin de saveDoc (cette fonction detruit declaration, on aurait pu utiliser InsertEndChild qui en aurait fait une copie)

    //Creation de l'element save
    TiXmlElement *saveInfo = new TiXmlElement("save");
    time_t saveDate;
    time(&saveDate);
    saveInfo->SetAttribute("firstSave",int(saveDate));
    saveInfo->SetAttribute("lastSave",int(saveDate));

    saveDoc.LinkEndChild(saveInfo);

    //Creation de l'element XML systeme et parametrage
    TiXmlElement *systemSave = new TiXmlElement("system");

    location="home";
    systemSave->SetAttribute("location",location);

    weather="sunny";
    systemSave->SetAttribute("weather",weather);

    systemSave->SetAttribute("timeSpeed",timeSpeed);

    saveDoc.LinkEndChild(systemSave);


    //Creation du tamagotchi
    string raceChoice;
    pet=new Tamagotchi(petRace,petName);
    TiXmlElement *petSave = new TiXmlElement("tamagotchi");

    //Modification des attributs du Tamagotchi
    pet->setThirst(60);
    pet->setHunger(30);
    pet->setTiredness(0);
    pet->setSocial(80);
    pet->setHygiene(20);
    pet->setBusiness(0);
    pet->setMood(50);
    pet->setAffection(0);
    pet->setSleep(false);
    pet->setLife(100.0);

    petSave->SetAttribute("name",pet->getName());
    petSave->SetAttribute("race",pet->getRace());
    petSave->SetAttribute("thirst",pet->getThirst());
    petSave->SetAttribute("hunger",pet->getHunger());
    petSave->SetAttribute("tiredness",pet->getTiredness());
    petSave->SetAttribute("social",pet->getSocial());
    petSave->SetAttribute("hygiene",pet->getHygiene());
    petSave->SetAttribute("business",pet->getBusiness());
    petSave->SetAttribute("mood",pet->getMood());
    petSave->SetAttribute("affection",pet->getAffection());
    petSave->SetAttribute("sleep",pet->getSleep());
    petSave->SetAttribute("life",pet->getLife());

    TiXmlElement *diseaseSave=new TiXmlElement("disease");
    diseaseSave->SetAttribute("progression","-1");
    petSave->LinkEndChild(diseaseSave);

    systemSave->LinkEndChild(petSave);

    ostringstream convert;
    convert<<saveDate;
    saveName=pet->getName()+"_"+convert.str()+".xml";//nom du fichier = petName_date.xml
    if(!saveDoc.SaveFile(saveName)) //on sauvegarde les modifications sur le fichier
    {
        cerr<<"Erreur lors de la creation du fichier de sauvegarde "<<saveName<<endl;
        cerr<<"error #"<<saveDoc.ErrorId()<<" : "<<saveDoc.ErrorDesc()<<endl;
        return false;
    }

    //on �dite le fichier r�pertoriant les sauvegardes
    string Info="info";
	ofstream fileInfo(Info.c_str(), ios::app);
	fileInfo << saveName << "\n";
	fileInfo.close();

    return true;
}

bool System::loadGame(string saveFile)
{
    TiXmlDocument saveDoc(saveFile.c_str());//recuperation du fichier
    if(!saveDoc.LoadFile())
    {
        cerr<<"Erreur lors du chargement du fichier de sauvegarde "<<saveFile<<endl;
        cerr<<"error #"<<saveDoc.ErrorId()<<" : "<<saveDoc.ErrorDesc()<<endl;
        return false;
    }

    //TiXmlElement saveInfo=saveDoc.FirstChild(); //methode simple pour recuperer le premier elem du fichier
    TiXmlHandle hdl(&saveDoc);//permet de securiser la  recuperation des donnees, le handle teste la presence de noeud a chaque changement, on peut alors faire hdl.child.child sans risque de bug de pointeur null


    //Recuperation des informations sur la sauvegarde
    TiXmlElement *saveInfo = hdl.FirstChildElement("save").ToElement();
    int dateConverter;
    saveInfo->QueryIntAttribute("lastSave", &dateConverter);
    time_t lastSave=dateConverter;


    //Recuperation des informations systeme
    TiXmlElement *systemSave = hdl.FirstChildElement("system").ToElement();
    if(!systemSave)
    {
        cerr<<"Erreur lors de la recuperation des donnees du systeme (noeud introuvable)."<<endl;
        return false;
    }
    location=systemSave->Attribute("location");
    weather=systemSave->Attribute("weather");
    float floatAttribute;//pour pouvoir recuperer directement un float au lieu d'une string
    systemSave->QueryFloatAttribute("timeSpeed",&floatAttribute);//convertit l'attribut en float et le stocke dans floatAttribute
    timeSpeed=floatAttribute;


    //Recuperation de l'element tamagotchi
    TiXmlElement *petSave = hdl.FirstChildElement("system").FirstChildElement("tamagotchi").ToElement();
    if(!petSave)
    {
        cerr<<"Erreur lors de la recuperation des donnees du Tamagotchi (noeud introuvable)."<<endl;
        return false;
    }

    pet=new Tamagotchi();//on instancie le Tamagotchi

    //Recuperation des attributs du Tamagotchi
    pet->setRace(petSave->Attribute("race"));
    pet->setName(petSave->Attribute("name"));
    
    petSave->QueryFloatAttribute("thirst",&floatAttribute);
    pet->setThirst(floatAttribute);
    petSave->QueryFloatAttribute("hunger",&floatAttribute);
    pet->setHunger(floatAttribute);
    petSave->QueryFloatAttribute("tiredness",&floatAttribute);
    pet->setTiredness(floatAttribute);
    petSave->QueryFloatAttribute("social",&floatAttribute);
    pet->setSocial(floatAttribute);
    petSave->QueryFloatAttribute("hygiene",&floatAttribute);
    pet->setHygiene(floatAttribute);
    petSave->QueryFloatAttribute("business",&floatAttribute);
    pet->setBusiness(floatAttribute);
    petSave->QueryFloatAttribute("mood",&floatAttribute);
    pet->setMood(floatAttribute);
    cout << "ICIIIIIII:    " << floatAttribute << endl; 
    petSave->QueryFloatAttribute("affection",&floatAttribute);
    pet->setAffection(floatAttribute);

    int intAttribute;//pour pouvoir recuperer directement un int au lieu d'une string

    petSave->QueryIntAttribute("life",&intAttribute);
    pet->setLife(intAttribute);

    bool boolAttribute;
    petSave->QueryBoolAttribute("sleep",&boolAttribute);
    pet->setSleep(boolAttribute);

    petSave->FirstChildElement("disease");
    if(!petSave)
    {
        cerr<<"Erreur lors de la recuperation des donnees du Tamagotchi (disease non trouve)."<<endl;
        return false;
    }
    petSave->QueryIntAttribute("progression", &intAttribute);
    if(intAttribute<0) //pet non malade
    {
        pet->setDisease(NULL);
    }
    else
    {
        Disease *petDisease=new Disease(intAttribute);
        petSave->QueryBoolAttribute("vet",&boolAttribute);
        petDisease->setVet(boolAttribute);
        if(boolAttribute)//si le veto a ete consulte on recupere les informations supplementaires sur la maladie
        {
            petSave->QueryIntAttribute("interval",&intAttribute);
            petDisease->setInterval(intAttribute);
            petSave->QueryIntAttribute("lastHeal",&intAttribute);
            petDisease->setLastHeal(intAttribute);
        }

        pet->setDisease(petDisease);
    }


    if(!update(lastSave))//on met a jour les donnees selon le temps ecoule depuis la derniere sauvegarde
    {
        cerr<<"Erreur lors du calcul de mise a jour de la partie."<<endl;
        return false;
    }
    saveName=saveFile;
    return true;
}

bool System::saveGame()
{
    TiXmlDocument saveDoc(saveName);//recuperation du fichier (copie les donnees en memoire)
    if(!saveDoc.LoadFile())
    {
        cerr<<"Erreur lors du chargement du fichier de sauvegarde "<<saveName<<endl;
        cerr<<"error #"<<saveDoc.ErrorId()<<" : "<<saveDoc.ErrorDesc()<<endl;
        return false;
    }

    TiXmlHandle hdl(&saveDoc);//permet de securiser la  recuperation des donnees, le handle teste la presence de noeud a chaque changement, on peut alors faire hdl.child.child sans risque de bug de pointeur null

    //On modifie la date de sauvegarde
    TiXmlElement *saveInfo = hdl.FirstChildElement("save").ToElement();
    if(!saveInfo)
    {
        cerr<<"Erreur lors de l'enregistrement des informations sur la sauvegarde (noeud introuvable)."<<endl;
        return false;
    }
    time_t saveDate;
    time(&saveDate);
    saveInfo->SetAttribute("lastSave",int(saveDate));
    cout<<"Date de sauvegarde modifiee : "<<saveInfo->Attribute("lastSave")<<endl;


    //Modification des informations systeme
    TiXmlElement *systemSave = hdl.FirstChildElement("system").ToElement();
    if(!systemSave)
    {
        cerr<<"Erreur lors de la recuperation des donnees du systeme (noeud introuvable)."<<endl;
        return false;
    }

    systemSave->SetAttribute("location",location);
    systemSave->SetAttribute("weather",weather);
    systemSave->SetAttribute("timeSpeed",timeSpeed);


    //Recuperation de l'element tamagotchi
    TiXmlElement *petSave = hdl.FirstChildElement("system").FirstChildElement("tamagotchi").ToElement();
    if(!petSave)
    {
        cerr<<"Erreur lors de la recuperation des donnees du Tamagotchi (noeud introuvable)."<<endl;
        return false;
    }

    //Modification des attributs du Tamagotchi
    petSave->SetAttribute("thirst",pet->getThirst());
    petSave->SetAttribute("hunger",pet->getHunger());
    petSave->SetAttribute("tiredness",pet->getTiredness());
    petSave->SetAttribute("social",pet->getSocial());
    petSave->SetAttribute("hygiene",pet->getHygiene());
    petSave->SetAttribute("business",pet->getBusiness());
    petSave->SetAttribute("mood",pet->getMood());
    petSave->SetAttribute("affection",pet->getAffection());
    petSave->SetAttribute("sleep",pet->getSleep());
    petSave->SetAttribute("life",pet->getLife());

    petSave->FirstChildElement("disease");
    if(!petSave)
    {
        cerr<<"Erreur lors de la recuperation des donnees du Tamagotchi (disease non trouve)."<<endl;
        return false;
    }

    if(pet->getDisease()==NULL) //pet non malade
    {
        petSave->SetAttribute("progression","-1");
    }
    else
    {
        petSave->SetAttribute( "progression", pet->getDisease()->getProgression() );
        petSave->SetAttribute( "vet", pet->getDisease()->getVet() );
        if( pet->getDisease()->getVet() )//si le veto a ete consulte on recupere les informations supplementaires sur la maladie
        {
            petSave->SetAttribute( "interval", pet->getDisease()->getInterval() );
            petSave->SetAttribute( "lastHeal", pet->getDisease()->getLastHeal() );
        }
    }


    if(!saveDoc.SaveFile(saveName)) //on sauvegarde les modifications sur le fichier
    {
        cerr<<"Erreur lors de la sauvegarde du fichier "<<saveName<<endl;
        cerr<<"error #"<<saveDoc.ErrorId()<<" : "<<saveDoc.ErrorDesc()<<endl;
        return false;
    }

    return true;
}

bool System::deleteGame(string saveFile)
{
	int i=0;
	string line="";
	string contents="";
	ifstream file("info", ios::in);
	ofstream fileInfo;
	if (file)
	{
		file.seekg(0,ios::beg);
		while ((getline(file, line)) && (line != saveFile)) { contents+=line+'\n'; }
		if (line != saveFile) { return false; }
		else
		{
			while (getline(file, line)) { contents+=line+'\n'; }
			string Info="info";
			fileInfo.open(Info.c_str(), ios::trunc);
			if (fileInfo)
			{
				fileInfo << contents;
				fileInfo.close();
				char f[100];
				for (i = 0; i < saveFile.length() ; i++) { f[i]=saveFile[i]; }
				remove(saveFile.c_str());
				return true;
			}
			else { return false; }
		}
	}
	else { return false; }
}


/***************************************
*********** ECRANS DE JEU **************
****************************************/

void System::newGameMenu()
{
    interface->displayNewGame();
    string event;
    bool loop=false;

    do
    {
		event=interface->waitEvent(); // Mise en pause du programme en attente d'un �v�nement
		if(event == "quit")
		{
			cout<<"Event quit"<<endl;
		}

		else if(event == "startNewGame")
		{
			string petName;
			interface->getTextInput(petName); //on r�cup�re le texte saisi par l'utilisateur
			cout<<"Nom Tamagotchi = "<<petName<<endl;
			if(petName.size()<2) cout<<"Nom trop court !"<<endl;
			else
			{
				interface->displayNewGameRace();
				event=interface->waitEvent();
				cout<<"Cr�ation du ficher de sauvegarde en cours...";
				if(!newGame(petName, event)) //on cr�e la sauvegarde
				{
					cerr<<"System (newGameMenu) > Erreur, impossible de cr�er une nouvelle partie."<<endl;
					loop=true;
				}
				else //si la cr�ation de partie a fonctionn�
				{
					mainMenu(); //on retourne au menu principal (on pourrait lancer directement la partie mais c'est mieux comme �a pour tester)
				}
			}
		}

		else if(event == "mainMenu")
		{
			mainMenu();
		}

		else
		{
			cerr<<"System (newGameMenu) > Evenement inconnu ignore: "<<event<<endl;
			loop=true;
		}

	} while(loop==true);//on boucle tant qu'un evenement connu (dont on a pr�vu les effets) ne survient pas

}

void System::loadGameMenu()
{
    interface->displayLoadGame();
    string event;
    bool loop;

    do
    {
    	loop=false;
		event=interface->waitEvent(); // Mise en pause du programme en attente d'un �v�nement
		if(event == "quit")
		{
			cout<<"Event quit"<<endl;
		}

		else if(event == "mainMenu")
		{
			mainMenu();
		}

		else //si l'event n'est pas un bouton pr�d�fini (ci-dessus) c'est que le joueur � cliqu� sur une partie � charger ou qu'un �v�nement inconnu s'est produit
		{
			if(!loadGame(event))
			{
				cerr<<"System (loadGameMenu) > Sauvegarde introuvable ou evenement inconnu: "<<event<<endl;
				loop=true;
			}
			else //si le chargement s'est bien pass�
			{
				runGame();
			}
		}

	}while(loop==true);

}

void System::deleteGameMenu()
{
    interface->displayDeleteGame();
    string event;
    bool loop;

    do
    {
    	loop=false;
		event=interface->waitEvent(); // Mise en pause du programme en attente d'un �v�nement
		if(event == "quit")
		{
			cout<<"Event quit"<<endl;
		}

		else if(event == "mainMenu")
		{
			mainMenu();
		}

		else //si l'event n'est pas un bouton pr�d�fini (ci-dessus) c'est que le joueur � cliqu� sur une partie � supprimer ou qu'un �v�nement inconnu s'est produit
		{
			if(!deleteGame(event))
			{
				cerr<<"System (deleteGameMenu) > Sauvegarde introuvable ou evenement inconnu: "<<event<<endl;
				loop=true;
			}
			else //si le chargement s'est bien pass�
			{
				cout << "Partie supprimer" << endl;
				mainMenu();
			}
		}

	}while(loop==true);

}

void System::runGame()
{
	string event;
    bool loop;

    interface->displayGame(pet);

    do
    {
    	loop=true;
    	if (pet->getLife() <= 0.0) { interface->displayDead(); }
		event=interface->waitEvent(10000); // Mise en pause du programme en attente d'un �v�nement
		update(); //d�s que l'on sort de l'attente d'un evenement on met a jour les stats du pet
		if(event == "quit")
		{
			cout<<"Event quit"<<endl;
			saveGame();
			loop=false;
		}
		
		if(event == "menu")
		{
			cout<<"Event menu"<<endl;
			saveGame();
			loop=false;
			
			mainMenu();
		}

		else if(event == "displayGame") //Reli� au bouton "retour" dans GUI::displayGauges
		{
			interface->displayGame(pet);
		}

		else if(event == "displayGauges") //Reli� au bouton "displayGauges" dans GUI::displayGame
		{
			interface->displayGauges(pet);
		}

		else if(event == "feed")
		{
			cout<<"feed"<<endl;
			feed(30);
			interface->displayGame(pet);
		}

		else if(event == "giveDrink")
		{
			cout<<"giveDrink"<<endl;
			giveDrink(20);
			interface->displayGame(pet);
		}
		
		else if(event == "doBusiness")
		{
			cout<<"doBusiness"<<endl;
			doBusiness();
			interface->displayGame(pet);
		}

		else if(event == "wakeUp")
		{
			cout<<"wakeUp"<<endl;
			wakeUp();
			interface->displayGame(pet);
		}

		else if(event == "heal")
		{
			cout<<"heal"<<endl;
			heal(1);//calcul� selon la maladie
			interface->displayGame(pet);
		}

		else if(event == "wash")
		{
			cout<<"wash"<<endl;
			wash(50);
			interface->displayGame(pet);
		}
		
		else if(event == "play")
		{
			cout<<"play"<<endl;
			play(20);
			interface->displayGame(pet);
		}

		else if(event == "playMini")
		{
			cout<<"playMini"<<endl;
			playMini();
		}

		else if(event == "goOut")
		{
			cout<<"goOut"<<endl;
			interface->displayParc(pet);
			//goOut();
		}
		
		else if(event == "home")
		{
			cout<<"home"<<endl;
			interface->displayGame(pet);
		}

		else if(event == "feedP")
		{
			cout<<"feedP"<<endl;
			feed(30);
			interface->displayParc(pet);
		}

		else if(event == "giveDrinkP")
		{
			cout<<"giveDrinkP"<<endl;
			giveDrink(20);
			interface->displayParc(pet);
		}
		
		
		else if(event == "playP")
		{
			cout<<"playP"<<endl;
			play(20);
			interface->displayParc(pet);
		}
		
		else if(event == "wakeUpP")
		{
			cout<<"wakeUpP"<<endl;
			wakeUp();
			interface->displayParc(pet);
		}
		
		else if(event == "displayGaugesParc") //Reli� au bouton "displayGaugesParc" dans GUI::displayParc
		{
			interface->displayGaugesParc(pet);
		}
		
		else if(event == "timeout")
			{
				cout<<"Mise � jour automatique."<<endl;
			}

		else
		{
			cerr<<"System (runGame) > Evenement inconnu ignore: "<<event<<endl;
		}

	} while(loop==true);
}

void System::feed(float n)
{
    if(pet->getHunger()<25) //si le Tamagotchi n'avait pas faim
    {
        pet->setMood(pet->getMood()-10); //son humeur diminue
        pet->setAffection(pet->getAffection()-2);
        //possibilit� de tomber malade
    }
    else pet->setAffection(pet->getAffection()+2); //si le Tamagotchi avait faim son affection augmente

	pet->setHunger(pet->getHunger()-n); //on le nourrit
	pet->setBusiness(pet->getBusiness()+n/2); //augmentation des petits besoins
}

void System::giveDrink(float n)
{
    if(pet->getThirst()<25) //si le Tamagotchi n'avait pas soif
    {
        pet->setMood(pet->getMood()-5); //son humeur diminue
        pet->setAffection(pet->getAffection()-1);
        //faible possibilit� de tomber malade
    }
    else pet->setAffection(pet->getAffection()+1); //si le Tamagotchi avait soif son affection augmente

	pet->setThirst(pet->getThirst()-n);
	pet->setBusiness(pet->getBusiness()+n/2); //augmentation des petits besoins
}

void System::doBusiness()
{
    //si le Tamagotchi n'avait pas envie il ne fait pas ses petits besoins, sinon ils tombent � 0
    if(pet->getBusiness()<25)
    {
        pet->setMood(pet->getMood()-5);
    }

	else
    {
        pet->setAffection(pet->getAffection()+1);
        pet->setBusiness(0);
    }
}

void System::wakeUp()
{
    if(pet->getSleep()==true)//si le Tamagotchi dort
    {
        if(pet->getTiredness()>25) //si le Tamagotchi est toujours fatigu�
        {
            pet->setMood(pet->getMood()- 5*pet->getTiredness()/25); //son humeur diminue (de -5 � -20)
        }

        pet->setSleep(false);
    }
}

void System::heal(int n)
{
	//interragis avec disease pas avec life
}

void System::wash(float n)
{
    if(pet->getHygiene()<50 || (pet->getMood()<25 && pet->getTiredness()>75) )
    {
        pet->setMood(pet->getMood()-10);
    }
    else pet->setAffection(pet->getAffection()+1);

	pet->setHygiene(pet->getHygiene()-n);
	pet->setBusiness(pet->getBusiness()+n/4);
}

void System::play(float n)
{
    if(pet->getSocial()<25 && (pet->getMood()<25 || pet->getTiredness()>75) ) //si le Tamagotchi n'a pas envie de jouer et qu'il est de mauvaise humeur ou fatigu� il refuse de jouer
    {
        pet->setMood(pet->getMood()-5);
        pet->setAffection(pet->getAffection()-1);
    }
    else
    {
        pet->setSocial(pet->getSocial()-n);
        pet->setAffection(pet->getAffection()+3);
        pet->setTiredness(pet->getTiredness()+n/4);
    }
}

void System::playMini()
{

}

void System::goOut()
{

}


void System::mainMenu()
{
	cout<<"Tamagotchi !"<<endl;

    interface->displayMainMenu();
    string event;
    bool loop;

    do
    {
    	loop=false;
		event=interface->waitEvent(); // Mise en pause du programme en attente d'un �v�nement
		if(event == "quit")
		{
			cout<<"Event quit"<<endl;
		}

		else if(event == "newGame")
		{
			cout<<"Nouvelle partie"<<endl;
			newGameMenu();
		}

		else if(event == "loadGame")
		{
			cout<<"Charger partie"<<endl;
			loadGameMenu();
		}
		
		else if(event == "deleteGame")
		{
			cout<<"Delete partie"<<endl;
			deleteGameMenu();
		}

		else
		{
			cerr<<"System (mainMenu) > Evenement inconnu ignore: "<<event<<endl;
			loop=true;
		}

	} while(loop==true);

}

