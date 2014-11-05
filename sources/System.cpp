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
    int elapsedTime=difftime(time(NULL),lastTime); //Calcul du temps ecoule depuis la derniere sauvegarde
    cout<<"Temps ecoule : "<<elapsedTime<<" secondes."<<endl;

    if(elapsedTime<0)//si la sauvegarde est posterieure a la date actuelle (travel time!)
    {
        cerr<<"Impossible de mettre a jour les donnees de la partie !"<<endl;
        cerr<<"Erreur: La date de derniere sauvegarde est plus recente que la date actuelle("<<elapsedTime<<"), la sauvegarde a peut-être ete corrompue ou le systemen n'est pas a l'heure."<<endl;
        return false;
    }

    if(elapsedTime>0)//comme ça si elapsedTime==0 on ne fait rien (ne devrait pas arriver)
    {
        elapsedTime/=60;//conversion en minutes
        pet->setThirst( pet->getThirst() + thirstDecay*elapsedTime );
        pet->setHunger( pet->getHunger() + hungerDecay*elapsedTime );
        pet->setTiredness( pet->getTiredness() + tirednessDecay*elapsedTime );
        pet->setSocial( pet->getSocial() + socialDecay*elapsedTime );
        pet->setHygiene( pet->getHygiene() + hygieneDecay*elapsedTime );
        pet->setBusiness( pet->getBusiness() + businessDecay*elapsedTime );
    }
    return true;
}

bool System::newGame()
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

    int intAttribute;//pour pouvoir recuperer directement un int au lieu d'une string

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

void System::mainMenu()
{
    int choix;
    cout<<"Tamagotchi !"<<endl;
    cout<<"1 - Nouvelle partie"<<endl;
    cout<<"2 - Charger partie"<<endl;
    cout<<"3 - Charger et sauvegarder"<<endl;
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
            loadGame(saveFile);
            saveGame();
        }
    }
}
