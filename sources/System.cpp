#include "../headers/System.h"

using namespace std;

System::System()
{
    //pet=new Tamagotchi();
    pet=NULL;
    //interface=new GUI();
    interface=NULL;

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


    //Récupération de l'élément tamagotchi
    TiXmlElement *petSave = hdl.FirstChildElement("system").FirstChildElement("tamagotchi").ToElement();
    if(!petSave)
    {
        cerr<<"Erreur lors de la recupértion des donnees du Tamagotchi."<<endl;
        return false;
    }

    pet=new Tamagotchi();//on instancie le Tamagotchi

    //Récupération des attributs du Tamagotchi
    pet->setRace(petSave->Attribute("race"));
    pet->setName(petSave->Attribute("name"));

    int intAttribute;//pour récupérer directement un int
    petSave->QueryIntAttribute("thirst",&intAttribute);
    pet->setThirst(intAttribute);
    petSave->QueryintAttribute("hunger",&intAttribute);
    pet->setHunger(intAttribute);
    petSave->QueryintAttribute("tiredness",&intAttribute);
    pet->setTiredness(intAttribute);
    petSave->QueryintAttribute("social",&intAttribute);
    pet->setSocial(intAttribute);
    petSave->QueryintAttribute("hygiene",&intAttribute);
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


    if(!update(lastSave))//on met à jour les données selon le temps écoulé depuis la dernière sauvegarde
    {
        cerr<<"Erreur lors du calcul de mise à jour de la partie."<<endl;
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
    cout<<"3 - Quitter"<<endl;
    cin>>choix;
    if(choix==2)
    {
        string saveFile;
        cout<<"Quelle partie voulez vous charger ?"<<endl;
        cin>>saveFile;
        loadGame(saveFile);
    }
}

int main()
{
    System system;//on crée une instance du jeu
    system.mainMenu();//démarre le jeu

    return 0;
}
