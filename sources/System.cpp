#include "../headers/System.h"

using namespace std;

System::System()
{
    //pet=new Tamagotchi();
    pet=NULL;
    //interface=new GUI();
    interface=NULL;

}

bool System::loadGame(string saveFile)
{
    TiXmlDocument saveDoc(saveFile.c_str());
    if(!saveDoc.LoadFile())
    {
        cerr<<"Erreur lors du chargement du fichier de sauvegarde "<<saveFile<<endl;
        cerr<<"error #"<<saveDoc.ErrorId()<<" : "<<saveDoc.ErrorDesc()<<endl;
        return false;
    }

    //TiXmlElement petSave=saveDoc.FirstChild(); //méthode simple pour récupérer le premier elem du fichier
    TiXmlHandle hdl(&saveDoc);//permet de sécuriser la  récupération des données
    TiXmlElement *petSave = hdl.FirstChildElement().Element();

    if(!petSave)
    {
        cerr<<"Erreur lors de la récupértion des données du Tamagotchi"<<endl;
        return false;
    }
    cout<<petSave->Attribute("name")<<" est un "<<petSave->Attribute("race")<<endl;
    int affection;
    petSave->QueryIntAttribute("affection", &affection);
    if(affection>=100) cout<<"Votre compagnon vous aime à la folie ! ("<<affection<<")"<<endl;

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
    cout<<"compilation ok !"<<endl;

    System system;
    system.mainMenu();

    return 0;
}
