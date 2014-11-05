#include "../headers/System.h"

using namespace std;

System::System()
{
    //pet=new Tamagotchi(); l'intanciation se fait au chargement de partie
    pet=NULL;
    //interface=new GUI();
    interface=NULL;
    location="undefined";
    weather="undefined";
    timeSpeed=1.0;
    endGame=false;
    endProgram=false;
}

bool System::update(const time_t &lastTime)
{
    int elapsedTime=difftime(time(NULL),lastTime); //Calcul du temps écoulé depuis la dernière sauvegarde
    cout<<"Temps ecoule : "<<elapsedTime<<" secondes."<<endl;

    if(elapsedTime<0)//si la sauvegarde est postèrieure à la date actuelle (travel time!)
    {
        cerr<<"Impossible de mettre à jour les donnees de la partie !"<<endl;
        cerr<<"Erreur: La date de derniere sauvegarde est plus recente que la date actuelle("<<elapsedTime<<"), la sauvegarde a peut-être été corrompue ou le systèmen n'est pas à l'heure."<<endl;
        return false;
    }

    if(elapsedTime>0)//comme ça si elapsedTime==0 on ne fait rien (ne devrait pas arriver)
    {
        elapsedTime/=60;//conversion en minutes
        //pet->setThirst( pet->getThirst() + thirstDecay*elapsedTime );
        cout<<"La soif du Tamagotchi a augmente de "<<thirstDecay*elapsedTime<<endl;
    }
    return true;
}

bool System::newGame()
{
    TiXmlDocument saveDoc;

    TiXmlDeclaration *declaration=new TiXmlDeclaration("1.0","UTF-8","yes");
    saveDoc.LinkEndChild(declaration);//on ajoute la déclaration à la fin de saveDoc (cette fonction détruit declaration, on aurait pu utiliser InsertEndChild qui en aurait fait une copie)

    //Création de l'élément save
    TiXmlElement *saveInfo = new TiXmlElement("save");
    time_t saveDate;
    time(&saveDate);
    saveInfo->SetAttribute("firstSave",int(saveDate));
    saveInfo->SetAttribute("lastSave",int(saveDate));

    saveDoc.LinkEndChild(saveInfo);

    //Création de l'élément XML système et paramètrage
    TiXmlElement *systemSave = new TiXmlElement("system");

    location="home";
    systemSave->SetAttribute("location",location);

    weather="sunny";
    systemSave->SetAttribute("weather",weather);

    systemSave->SetAttribute("timeSpeed",timeSpeed);

    saveDoc.LinkEndChild(systemSave);


    //Création du tamagotchi
    string raceChoice, nameChoice;
    cout<<"Comment voulez-vous appeler votre Tamagotchi ?";
    cin>>nameChoice;
    pet=new Tamagotchi("chat",nameChoice);
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
    pet->setLife(100);

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

    string saveName="";
    ostringstream convert;
    convert<<saveDate;
    //int saveDateInt=saveDate;
    //string saveDateString(saveDateInt);
    saveName=pet->getName()+"_"+convert.str()+".xml";
    if(!saveDoc.SaveFile(saveName)) //on sauvegarde les modifications sur le fichier
    {
        cerr<<"Erreur lors de la creation du fichier de sauvegarde "<<saveName<<endl;
        cerr<<"error #"<<saveDoc.ErrorId()<<" : "<<saveDoc.ErrorDesc()<<endl;
        return false;
    }

    return true;
}

bool System::loadGame(string saveFile)
{
    TiXmlDocument saveDoc(saveFile.c_str());//récupération du fichier
    if(!saveDoc.LoadFile())
    {
        cerr<<"Erreur lors du chargement du fichier de sauvegarde "<<saveFile<<endl;
        cerr<<"error #"<<saveDoc.ErrorId()<<" : "<<saveDoc.ErrorDesc()<<endl;
        return false;
    }

    //TiXmlElement saveInfo=saveDoc.FirstChild(); //méthode simple pour récupérer le premier elem du fichier
    TiXmlHandle hdl(&saveDoc);//permet de sécuriser la  récupération des données, le handle teste la présence de noeud à chaque changement, on peut alors faire hdl.child.child sans risque de bug de pointeur null


    //Récupération des informations sur la sauvegarde
    TiXmlElement *saveInfo = hdl.FirstChildElement("save").ToElement();
    int dateConverter;
    saveInfo->QueryIntAttribute("lastSave", &dateConverter);
    time_t lastSave=dateConverter;


    //Récupération des informations système
    TiXmlElement *systemSave = hdl.FirstChildElement("system").ToElement();
    if(!systemSave)
    {
        cerr<<"Erreur lors de la recuperation des donnees du systeme (noeud introuvable)."<<endl;
        return false;
    }
    location=systemSave->Attribute("location");
    weather=systemSave->Attribute("weather");
    float floatAttribute;//pour pouvoir récupérer directement un float au lieu d'une string
    systemSave->QueryFloatAttribute("timeSpeed",&floatAttribute);//convertit l'attribut en float et le stocke dans floatAttribute
    timeSpeed=floatAttribute;


    //Récupération de l'élément tamagotchi
    TiXmlElement *petSave = hdl.FirstChildElement("system").FirstChildElement("tamagotchi").ToElement();
    if(!petSave)
    {
        cerr<<"Erreur lors de la recuperation des donnees du Tamagotchi (noeud introuvable)."<<endl;
        return false;
    }

    pet=new Tamagotchi();//on instancie le Tamagotchi

    //Récupération des attributs du Tamagotchi
    pet->setRace(petSave->Attribute("race"));
    pet->setName(petSave->Attribute("name"));

    int intAttribute;//pour pouvoir récupérer directement un int au lieu d'une string

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
    petSave->QueryIntAttribute("life",&intAttribute);
    pet->setLife(intAttribute);

    bool boolAttribute;
    petSave->QueryBoolAttribute("sleep",&boolAttribute);
    pet->setSleep(boolAttribute);

    petSave->FirstChildElement("disease");
    if(!petSave)
    {
        cerr<<"Erreur lors de la recuperation des donnees du Tamagotchi (disease non trouvé)."<<endl;
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
        if(boolAttribute)//si le veto a été consulté on récupère les informations supplémentaires sur la maladie
        {
            petSave->QueryIntAttribute("interval",&intAttribute);
            petDisease->setInterval(intAttribute);
            petSave->QueryIntAttribute("lastHeal",&intAttribute);
            petDisease->setLastHeal(intAttribute);
        }

        pet->setDisease(petDisease);
    }


    if(!update(lastSave))//on met à jour les données selon le temps écoulé depuis la dernière sauvegarde
    {
        cerr<<"Erreur lors du calcul de mise à jour de la partie."<<endl;
        return false;
    }
    return true;
}

bool System::saveGame()
{
    TiXmlDocument saveDoc(saveName);//récupération du fichier (copie les données en mémoire)
    if(!saveDoc.LoadFile())
    {
        cerr<<"Erreur lors du chargement du fichier de sauvegarde "<<saveName<<endl;
        cerr<<"error #"<<saveDoc.ErrorId()<<" : "<<saveDoc.ErrorDesc()<<endl;
        return false;
    }

    TiXmlHandle hdl(&saveDoc);//permet de sécuriser la  récupération des données, le handle teste la présence de noeud à chaque changement, on peut alors faire hdl.child.child sans risque de bug de pointeur null

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


    //Modification des informations système
    TiXmlElement *systemSave = hdl.FirstChildElement("system").ToElement();
    if(!systemSave)
    {
        cerr<<"Erreur lors de la recuperation des donnees du systeme (noeud introuvable)."<<endl;
        return false;
    }

    systemSave->SetAttribute("location",location);
    systemSave->SetAttribute("weather",weather);
    systemSave->SetAttribute("timeSpeed",timeSpeed);


    //Récupération de l'élément tamagotchi
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
        cerr<<"Erreur lors de la recuperation des donnees du Tamagotchi (disease non trouvé)."<<endl;
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
        if( pet->getDisease()->getVet() )//si le veto a été consulté on récupère les informations supplémentaires sur la maladie
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
    switch(choix)
    {
        case 1:
        {
            newGame();
            break;
        }

        case 2:
        {
            string saveFile;
            cout<<"Quelle partie voulez vous charger ?"<<endl;
            cin>>saveFile;
            loadGame(saveFile);
            break;
        }

        case 3:
        {
            string saveFile;
            cout<<"Quelle sauvegarde voulez vous modifier ?"<<endl;
            cin>>saveFile;
            saveName=saveFile;
            saveGame();
        }
    }
}
