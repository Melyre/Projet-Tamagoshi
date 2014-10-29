#include "../headers/System.h"

using namespace std;

System::System()
{
    //pet=new Tamagotchi(); l'intanciation se fait au chargement de partie
    pet=NULL;
    //interface=new GUI();
    interface=NULL;
    timeSpeed=1.0;
    endGame=false;
    endProgram=false;
}

bool System::update(const time_t &lastTime)
{
    int elapsedTime=difftime(time(NULL),lastTime); //Calcul du temps �coul� depuis la derni�re sauvegarde
    cout<<"Temps ecoule : "<<elapsedTime<<" secondes."<<endl;

    if(elapsedTime<0)//si la sauvegarde est post�rieure � la date actuelle (travel time!)
    {
        cerr<<"Impossible de mettre � jour les donnees de la partie !"<<endl;
        cerr<<"Erreur: La date de derniere sauvegarde est plus recente que la date actuelle("<<elapsedTime<<"), la sauvegarde a peut-�tre �t� corrompue ou le syst�men n'est pas � l'heure."<<endl;
        return false;
    }

    if(elapsedTime>0)//comme �a si elapsedTime==0 on ne fait rien (ne devrait pas arriver)
    {
        elapsedTime/=60;//conversion en minutes
        //pet->setThirst( pet->getThirst() + thirstDecay*elapsedTime );
        cout<<"La soif du Tamagotchi a augmente de "<<thirstDecay*elapsedTime<<endl;
    }
    return true;
}

bool System::loadGame(string saveFile)
{
    TiXmlDocument saveDoc(saveFile.c_str());//r�cup�ration du fichier
    if(!saveDoc.LoadFile())
    {
        cerr<<"Erreur lors du chargement du fichier de sauvegarde "<<saveFile<<endl;
        cerr<<"error #"<<saveDoc.ErrorId()<<" : "<<saveDoc.ErrorDesc()<<endl;
        return false;
    }

    //TiXmlElement saveInfo=saveDoc.FirstChild(); //m�thode simple pour r�cup�rer le premier elem du fichier
    TiXmlHandle hdl(&saveDoc);//permet de s�curiser la  r�cup�ration des donn�es, le handle teste la pr�sence de noeud � chaque changement, on peut alors faire hdl.child.child sans risque de bug de pointeur null


    //R�cup�ration des informations sur la sauvegarde
    TiXmlElement *saveInfo = hdl.FirstChildElement("save").ToElement();
    int dateConverter;
    saveInfo->QueryIntAttribute("lastSave", &dateConverter);
    time_t lastSave=dateConverter;


    //R�cup�ration des informations syst�me
    TiXmlElement *systemSave = hdl.FirstChildElement("system").ToElement();
    if(!systemSave)
    {
        cerr<<"Erreur lors de la recuperation des donnees du systeme (noeud introuvable)."<<endl;
        return false;
    }
    location=systemSave->Attribute("location");
    weather=systemSave->Attribute("weather");
    float floatAttribute;//pour pouvoir r�cup�rer directement un float au lieu d'une string
    systemSave->QueryFloatAttribute("timeSpeed",&floatAttribute);//convertit l'attribut en float et le stocke dans floatAttribute
    timeSpeed=floatAttribute;


    //R�cup�ration de l'�l�ment tamagotchi
    TiXmlElement *petSave = hdl.FirstChildElement("system").FirstChildElement("tamagotchi").ToElement();
    if(!petSave)
    {
        cerr<<"Erreur lors de la recuperation des donnees du Tamagotchi (noeud introuvable)."<<endl;
        return false;
    }

    pet=new Tamagotchi();//on instancie le Tamagotchi

    //R�cup�ration des attributs du Tamagotchi
    pet->setRace(petSave->Attribute("race"));
    pet->setName(petSave->Attribute("name"));

    int intAttribute;//pour pouvoir r�cup�rer directement un int au lieu d'une string

    petSave->QueryIntAttribute("thirst",&intAttribute);
    pet->setThirst(intAttribute);
    petSave->QueryIntAttribute("hunger",&intAttribute);
    pet->setHunger(intAttribute);
    petSave->QueryIntAttribute("tiredness",&intAttribute);
    pet->setTiredness(intAttribute);
    petSave->QueryIntAttribute("social",&intAttribute);
    pet->setSocial(intAttribute);
    petSave->QueryIntAttribute("hygiene",&intAttribute);
    pet->setHygiene(intAttribute);
    petSave->QueryIntAttribute("business",&intAttribute);
    pet->setBusiness(intAttribute);
    petSave->QueryIntAttribute("mood",&intAttribute);
    pet->setMood(intAttribute);
    petSave->QueryIntAttribute("affection",&intAttribute);
    pet->setAffection(intAttribute);

    bool boolAttribute;
    petSave->QueryBoolAttribute("sleep",&boolAttribute);
    pet->setSleep(boolAttribute);

    petSave->FirstChildElement("disease");
    if(!petSave)
    {
        cerr<<"Erreur lors de la recuperation des donnees du Tamagotchi (disease non trouv�)."<<endl;
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
        if(boolAttribute)//si le veto a �t� consult� on r�cup�re les informations suppl�mentaires sur la maladie
        {
            petSave->QueryIntAttribute("interval",&intAttribute);
            petDisease->setInterval(intAttribute);
            petSave->QueryIntAttribute("lastHeal",&intAttribute);
            petDisease->setLastHeal(intAttribute);
        }

        pet->setDisease(petDisease);
    }


    if(!update(lastSave))//on met � jour les donn�es selon le temps �coul� depuis la derni�re sauvegarde
    {
        cerr<<"Erreur lors du calcul de mise � jour de la partie."<<endl;
        return false;
    }
    return true;
}

bool System::saveGame()
{
    TiXmlDocument saveDoc(saveName);//r�cup�ration du fichier (copie les donn�es en m�moire)
    if(!saveDoc.LoadFile())
    {
        cerr<<"Erreur lors du chargement du fichier de sauvegarde "<<saveName<<endl;
        cerr<<"error #"<<saveDoc.ErrorId()<<" : "<<saveDoc.ErrorDesc()<<endl;
        return false;
    }

    TiXmlHandle hdl(&saveDoc);//permet de s�curiser la  r�cup�ration des donn�es, le handle teste la pr�sence de noeud � chaque changement, on peut alors faire hdl.child.child sans risque de bug de pointeur null

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


    //Modification des informations syst�me
    TiXmlElement *systemSave = hdl.FirstChildElement("system").ToElement();
    if(!systemSave)
    {
        cerr<<"Erreur lors de la recuperation des donnees du systeme (noeud introuvable)."<<endl;
        return false;
    }

    systemSave->SetAttribute("location",location);
    systemSave->SetAttribute("weather",weather);
    systemSave->SetAttribute("timeSpeed",timeSpeed);


    //R�cup�ration de l'�l�ment tamagotchi
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

    petSave->FirstChildElement("disease");
    if(!petSave)
    {
        cerr<<"Erreur lors de la recuperation des donnees du Tamagotchi (disease non trouv�)."<<endl;
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
        if(boolAttribute)//si le veto a �t� consult� on r�cup�re les informations suppl�mentaires sur la maladie
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

void System::mainMenu()
{
    int choix;
    cout<<"Tamagotchi !"<<endl;
    cout<<"1 - Nouvelle partie"<<endl;
    cout<<"2 - Charger partie"<<endl;
    cout<<"3 - Test sauvegarde"<<endl;
    cout<<"4 - Quitter"<<endl;
    cin>>choix;
    if(choix==2)
    {
        string saveFile;
        cout<<"Quelle partie voulez vous charger ?"<<endl;
        cin>>saveFile;
        loadGame(saveFile);
    }
    else if(choix==3)
    {
        string saveFile;
        cout<<"Quelle sauvegarde voulez vous modifier ?"<<endl;
        cin>>saveFile;
        saveName=saveFile;
        saveGame();
    }
}

int main()
{
    System system;//on cr�e une instance du jeu
    system.mainMenu();//d�marre le jeu

    return 0;
}
