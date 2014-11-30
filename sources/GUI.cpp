#include "../headers/GUI.h"

SDL_Color GUI::BLACK = {0, 0, 0};
SDL_Color GUI::WHITE = {255, 255, 255};
/*SDL_Cursor * GUI::ARROW = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
SDL_Cursor * GUI::POINTER = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);*/

GUI::GUI()
{
	SDL_Init(SDL_INIT_VIDEO); // Initialisation de la SDL
	
	ARROW = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	POINTER = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	
	//screen=SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); // Ouverture et paramètres de la fenêtre (SDL 1)
	
	window = SDL_CreateWindow("Tamagotchi SDL 2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0); //SDL2
	screen = SDL_GetWindowSurface(window);//on crée la SDL_Window et on la convertit en SDL_Surface dans screen (SDL2)
	
	textInput[0]='\0';
}

GUI::~GUI()
{	
	clearButtons();
	
	SDL_DestroyWindow(window); //nécessaire pour SDL2
	
	SDL_Quit(); // Arrêt de la SDL
	
	cout<<"SDL quittee !"<<endl;
}


//Accesseurs

void GUI::getTextInput(string &dest)
{
	dest=textInput;
}

//Fonctions

string GUI::waitEvent()
{
    int stop = false;
    SDL_Event event;
 	string pressedButton(""), hoverButton("");
    while (!stop)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT: //croix / alt+f4...
                stop = true;
                return "quit";
                
            case SDL_MOUSEBUTTONUP: //clic
            	pressedButton=getButtonName(event.button.x,event.button.y); //on récupère le nom du bouton activé
            	cout << "SPOTTED ! buttonclick" << endl;
            	if(pressedButton=="clearInput") //pour effacer les champs texte (newGame...)
            	{ 
            		textInput[0]='\0';
            		displayNewGame();
            	}
            	else if(!pressedButton.empty())
            	{
            		cout << "SPOTTED ! " << pressedButton << endl;
            		return pressedButton; //si on a cliqué sur un bouton on renvoie son nom
            	}
            	
            	break;
            	
            case SDL_MOUSEMOTION: //déplacement souris
            	hoverButton=getButtonName(event.button.x,event.button.y);
            	if(!hoverButton.empty()) switchCursor(POINTER); //si le curseur passe sur un élément cliquable il devient un pointeur
            	else switchCursor(ARROW); //sinon on le remet en curseur par défaut
            	break;
            	
            case SDL_TEXTINPUT: //saisie de texte (uniquement lorsque textInput a été activé)
            	strcat(textInput, event.text.text);
            	//cout<<"input = "<<textInput<<endl;
            	displayNewGame();
            	break;
        }
    }
}


SDL_Rect GUI::centerPos(SDL_Surface *surface)
{
	SDL_Rect position;
	position.x = screen->w/2 - surface->w/2;
	position.y = screen->h/2 - surface->h/2;
	return position;
}

void GUI::addButton(SDL_Rect button, string buttonName)
{
	if(buttonName.empty())
	{
		cerr<<"Can't create a Button without a name or with an empty string name"<<endl;
		return;
	}
	
	Button newButton;
	newButton.rect=button;
	newButton.name=buttonName;
	buttons.push_back(newButton);//crée une copie du de newButton à la fin du vecteur
}

void GUI::clearButtons()
{
	buttons.clear();
}

string GUI::getButtonName(int x, int y)
{
	for(int i=0;i<buttons.size();i++)
	{
		if( x >= buttons[i].rect.x && y >= buttons[i].rect.y && x <= buttons[i].rect.x+buttons[i].rect.w && y <= buttons[i].rect.y+buttons[i].rect.h )
		{
			return buttons[i].name;
		}
	}
	return "";
}

void GUI::clearScreen()
{
	//on stoppe et efface la saisie de texte
	SDL_StopTextInput();
	
	clearButtons(); //buttons.clear(), vide le vecteur
	
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,0,0,0)); //on remplit la fenêtre de noir
}
	

void GUI::switchCursor(SDL_Cursor *cursor)
{
	//ne fonctionne pas si les curseurs sont en static ?!
	if(SDL_GetCursor()!=cursor) SDL_SetCursor(cursor); //si le curseur actuel est différent du nouveau curseur on change
}

/* A supprimer ?
void GUI::updateInput(char * textInput)
{
	if(TTF_Init() == -1)
	{
		cout<<"error in GUI::displayMenu, TTF_Init failed: "<<TTF_GetError()<<endl;
		return;
	}
	TTF_Font *font=NULL;
	font = TTF_OpenFont("../arial.ttf", 22);
	if(font == NULL)
	{
		cout<<"error in GUI::displayMenu, TTF_OpendFont failed: "<<TTF_GetError()<<endl;
		return;
	}
	
	SDL_Surface *text = TTF_RenderText_Blended(font, textInput, WHITE);
	SDL_Rect position;
	position.x=input->w/2 - text->w/2;
	position.y=input->h/2 - text->h/2;
    SDL_BlitSurface(text, NULL, input, &position);
    
    position.x = screen->w/2 - text->w/2;
    position.y = 225;
    SDL_BlitSurface(input, NULL, screen, &position);
    SDL_UpdateWindowSurface(window); //SDL2

	TTF_Quit();
}
*/

/***************************************
*********** ECRANS DE JEU **************
****************************************/

void GUI::displayMainMenu()
{
	clearScreen();

	SDL_Surface *text=NULL, *background=NULL;
    SDL_Rect position;
	
	if(TTF_Init() == -1)//initialisation de TTF, nécessaire pour écrire du texte
	{
		cout<<"error in GUI::displayMenu, TTF_Init failed: "<<TTF_GetError()<<endl;
		return;
	}
	TTF_Font *font=NULL;
	font = TTF_OpenFont("../arial.ttf", 22); //on règle la police que l'on souhaite utiliser
	if(font == NULL)
	{
		cout<<"error in GUI::displayMenu, TTF_OpendFont failed: "<<TTF_GetError()<<endl;
		return;
	}
	
	text = TTF_RenderText_Blended(font, "Tamagotchi", WHITE); //création d'une surface contenant un texte
	position.x = screen->w/2 - text->w/2; //positionnement horizontal (ici au centre de la fenetre)
	position.y = 0; //positionnement vertical (ici tout en haut de la fenetre)
    SDL_BlitSurface(text, NULL, screen, &position); //on applique la surface text entière sur notre fenetre (modification faites seulement en mémoire pour le moment)
    
    text = TTF_RenderText_Blended(font, "Nouvelle partie", WHITE);
    position.x = screen->w/2 - text->w/2;
    position.y = 75;
    SDL_BlitSurface(text, NULL, screen, &position);
	addButton(position,"newGame");
    
    text = TTF_RenderText_Blended(font, "Charger partie", WHITE);
    position.x = screen->w/2 - text->w/2;
    position.y = 150;
    SDL_BlitSurface(text, NULL, screen, &position);
    addButton(position,"loadGame");
    
    text = TTF_RenderText_Blended(font, "Quitter", WHITE);
    position.x = screen->w/2 - text->w/2;
    position.y = 225;
    SDL_BlitSurface(text, NULL, screen, &position);
    addButton(position,"quit");
    
    //SDL_Flip(screen); //SDL 1
    SDL_UpdateWindowSurface(window); //on met à jour l'affichage (selon les BlitSurface précedents) (SDL2)
	
	TTF_Quit();	//on libère TTF
}

void GUI::displayNewGame()
{
	clearScreen();

	SDL_Surface *text=NULL, *background=NULL;
    SDL_Rect position;
	
	if(TTF_Init() == -1)
	{
		cout<<"error in GUI::displayMenu, TTF_Init failed: "<<TTF_GetError()<<endl;
		return;
	}
	TTF_Font *font=NULL;
	font = TTF_OpenFont("../arial.ttf", 22);
	if(font == NULL)
	{
		cout<<"error in GUI::displayMenu, TTF_OpendFont failed: "<<TTF_GetError()<<endl;
		return;
	}
	
	text = TTF_RenderText_Blended(font, "Nouvelle partie", WHITE);
	position.x = screen->w/2 - text->w/2;
    position.y = 0;
    SDL_BlitSurface(text, NULL, screen, &position);
    
    text = TTF_RenderText_Blended(font, "Quel nom voulez-vous donner a votre Tamagotchi ?", WHITE);
    position.x = screen->w/2 - text->w/2;
    position.y = 100;
    SDL_BlitSurface(text, NULL, screen, &position);
    
    //on crée l'input
    input = SDL_CreateRGBSurface(0, 500, 30, 32, 0, 0, 0, 0);
    SDL_FillRect(input, NULL, SDL_MapRGB(screen->format,0,0,255));
    
    //on crée et positionne le texte saisi dans l'input
    if(textInput[0]!='\0')
    {
		text = TTF_RenderText_Blended(font, textInput, WHITE);
		position.x=input->w/2 - text->w/2;
		position.y=input->h/2 - text->h/2;
		SDL_BlitSurface(text, NULL, input, &position);
	}
    
    //positionnement de l'input
    position.x = screen->w/2 - input->w/2;
	position.y = 200;
    SDL_SetTextInputRect(&position);
    SDL_BlitSurface(input, NULL, screen, &position);
    
    text = TTF_RenderText_Blended(font, "Effacer", WHITE);
    position.x = screen->w/2 - text->w/2;
    position.y = position.y + input->h + 10; // /!\ position relative
    SDL_BlitSurface(text, NULL, screen, &position);
    addButton(position,"clearInput");
    
    text = TTF_RenderText_Blended(font, "Valider", WHITE);
    position.x = screen->w/2 - text->w/2;
    position.y = position.y + text->h + 10; // /!\ position relative
    SDL_BlitSurface(text, NULL, screen, &position);
    addButton(position,"startNewGame");
    
    text = TTF_RenderText_Blended(font, "Retour", WHITE);
    position.x = screen->w/2 - text->w/2;
    position.y = screen->h - text->h - 10;
    SDL_BlitSurface(text, NULL, screen, &position);
    addButton(position,"mainMenu");
    
    //SDL_Flip(screen); //SDL 1
    SDL_UpdateWindowSurface(window); //SDL2
    SDL_StartTextInput(); //active les évènements de saisie de texte et doit être stoppé avec SDL_StopTextInput(), on le stoppe donc au changement d'écran (clearScreen())

	TTF_Quit();	
}

void GUI::displayLoadGame()
{
	clearScreen();

	SDL_Surface *text=NULL, *background=NULL;
    SDL_Rect position;
	
	if(TTF_Init() == -1)
	{
		cout<<"error in GUI::displayMenu, TTF_Init failed: "<<TTF_GetError()<<endl;
		return;
	}
	TTF_Font *font=NULL;
	font = TTF_OpenFont("../arial.ttf", 22);
	if(font == NULL)
	{
		cout<<"error in GUI::displayMenu, TTF_OpendFont failed: "<<TTF_GetError()<<endl;
		return;
	}
	
	text = TTF_RenderText_Blended(font, "Charger partie", WHITE);
	position.x = screen->w/2 - text->w/2;
    position.y = 0;
    SDL_BlitSurface(text, NULL, screen, &position);
    
    //on cherche dans le fichier les sauvegardes existantes
    string line;
    ifstream file("info", ios::in);
	file.seekg(0,ios::beg);
	while (getline(file, line)) { }
	file.clear();
	int currentHeight=100;
	if (file.tellg() == 0)
	{
		text = TTF_RenderText_Blended(font, "Vous n'avez aucune sauvegarde", WHITE);
		position.x = screen->w/2 - text->w/2;
		position.y = currentHeight;
		SDL_BlitSurface(text, NULL, screen, &position);
	}
	else
	{
		file.seekg(0,ios::beg);
		while (getline(file, line))
		{
			text = TTF_RenderText_Blended(font, line.c_str(), WHITE);
			position.x = screen->w/2 - text->w/2;
			position.y = currentHeight;
			SDL_BlitSurface(text, NULL, screen, &position);
			addButton(position,line);
			currentHeight += text->h + 20;
		}
	}
    
    text = TTF_RenderText_Blended(font, "Retour", WHITE);
    position.x = screen->w/2 - text->w/2;
    position.y = screen->h - text->h - 10;
    SDL_BlitSurface(text, NULL, screen, &position);
    addButton(position,"mainMenu");
    
    //SDL_Flip(screen); //SDL 1
    SDL_UpdateWindowSurface(window); //SDL2
    SDL_StartTextInput();

	TTF_Quit();	
}

void GUI::displayGame(Tamagotchi * pet)
{	
	clearScreen();
	
	if(TTF_Init() == -1)
	{
		cout<<"error in GUI::displayMenu, TTF_Init failed: "<<TTF_GetError()<<endl;
		return;
	}
	TTF_Font *font=NULL;
	font = TTF_OpenFont("../arial.ttf", 22);
	if(font == NULL)
	{
		cout<<"error in GUI::displayMenu, TTF_OpendFont failed: "<<TTF_GetError()<<endl;
		return;
	}

	int gaugeWidth(0), gaugeBgWidth(100);
	SDL_Surface *text = NULL, * gaugeBackground = NULL, * fillGauge = NULL; 	
	SDL_Rect position, textPosition;

	gaugeBackground = SDL_CreateRGBSurface(0, gaugeBgWidth, 20, 32, 0, 0, 0, 0); // Le fond des jauges.
    SDL_FillRect(gaugeBackground, NULL, SDL_MapRGB(screen->format,128,128,128));
    
    pet->setMood(30);  // A ENLEVER QUAND LEVOLUTION DES STATS SERA FIXEE.
    gaugeWidth = (gaugeBgWidth * pet->getMood()) / 100; // Definit le remplissage des jauges (en % de la taille du fond).
    fillGauge = SDL_CreateRGBSurface(0, gaugeWidth, 20, 32, 0, 0, 0, 0);
    SDL_FillRect(fillGauge, NULL, SDL_MapRGB(screen->format,0,204,0));
    
    position.x = 2;
    position.y = 10;
    text = TTF_RenderText_Blended(font, "Humeur", WHITE);
    textPosition.x = position.x + gaugeBackground->w / 2 - text->w / 2;
    textPosition.y = position.y-2;
    SDL_BlitSurface(gaugeBackground, NULL, screen, &position);
    SDL_BlitSurface(fillGauge, NULL, screen, &position);
    SDL_BlitSurface(text, NULL, screen, &textPosition);
    
    text = TTF_RenderText_Blended(font, "Jauges", WHITE);
	position.x = screen->w / 2 - text->w / 2;
	position.y = 15;
    SDL_BlitSurface(text, NULL, screen, &position);
    addButton(position,"displayGauges");
    
    SDL_UpdateWindowSurface(window); 

	TTF_Quit();
}

void GUI::displayGauges(Tamagotchi * pet)
{
	clearScreen();
	SDL_Surface * text;
	SDL_Rect position;
	if(TTF_Init() == -1)
	{
		cout<<"error in GUI::displayMenu, TTF_Init failed: "<<TTF_GetError()<<endl;
		return;
	}
	TTF_Font *font=NULL;
	font = TTF_OpenFont("../arial.ttf", 22);
	if(font == NULL)
	{
		cout<<"error in GUI::displayMenu, TTF_OpendFont failed: "<<TTF_GetError()<<endl;
		return;
	}

	int yPosition(5);
	yPosition = displayGauge(pet, 1, yPosition);
	yPosition = displayGauge(pet, 2, yPosition);
	yPosition = displayGauge(pet, 3, yPosition);
	yPosition = displayGauge(pet, 4, yPosition);
	yPosition = displayGauge(pet, 5, yPosition);
	yPosition = displayGauge(pet, 6, yPosition);
	yPosition = displayGauge(pet, 7, yPosition);
	yPosition = displayGauge(pet, 8, yPosition);
	yPosition = displayGauge(pet, 9, yPosition);
	
	text = TTF_RenderText_Blended(font, "Retour", WHITE);
	position.x = screen->w / 2 - text->w / 2;
	position.y = yPosition + 15;
    SDL_BlitSurface(text, NULL, screen, &position);
    addButton(position,"displayGame");
        
    SDL_UpdateWindowSurface(window);
    TTF_Quit();
}

int GUI::displayGauge (Tamagotchi *pet, int type, int topMarge)
{
	if(TTF_Init() == -1)
	{
		cout<<"error in GUI::displayMenu, TTF_Init failed: "<<TTF_GetError()<<endl;
		return 0;
	}
	TTF_Font *font=NULL;
	font = TTF_OpenFont("../arial.ttf", 22);
	if(font == NULL)
	{
		cout<<"error in GUI::displayMenu, TTF_OpendFont failed: "<<TTF_GetError()<<endl;
		return 0;
	}	
	
	
	int gaugeWidth(0), gaugeBgWidth(400);
	SDL_Surface *text = NULL, * gaugeBackground = NULL, * fillGauge = NULL; 	
	SDL_Rect position, textPosition;

	gaugeBackground = SDL_CreateRGBSurface(0, gaugeBgWidth, 25, 32, 0, 0, 0, 0); // Le fond des jauges.
    SDL_FillRect(gaugeBackground, NULL, SDL_MapRGB(screen->format,128,128,128));
    
	switch(type)
	{
		case 1: 
			pet->setHunger(30);  // A ENLEVER QUAND LEVOLUTION DES STATS SERA FIXEE.
    		gaugeWidth = (gaugeBgWidth * pet->getHunger()) / 100;
    		text = TTF_RenderText_Blended(font, "Faim", WHITE);
			break;
			
		case 2:
			pet->setThirst(60);  // A ENLEVER QUAND LEVOLUTION DES STATS SERA FIXEE.
    		gaugeWidth = (gaugeBgWidth * pet->getThirst()) / 100;
    		text = TTF_RenderText_Blended(font, "Soif", WHITE);
			break;
			
		case 3:
			pet->setTiredness(0);  // A ENLEVER QUAND LEVOLUTION DES STATS SERA FIXEE.
    		gaugeWidth = (gaugeBgWidth * pet->getTiredness()) / 100;
    		text = TTF_RenderText_Blended(font, "Fatigue", WHITE);
			break;
			
		case 4:
			pet->setSocial(80);  // A ENLEVER QUAND LEVOLUTION DES STATS SERA FIXEE.
    		gaugeWidth = (gaugeBgWidth * pet->getSocial()) / 100;
    		text = TTF_RenderText_Blended(font, "Social", WHITE);
			break;
			
		case 5:
			pet->setHygiene(20);  // A ENLEVER QUAND LEVOLUTION DES STATS SERA FIXEE.
    		gaugeWidth = (gaugeBgWidth * pet->getHygiene()) / 100;
    		text = TTF_RenderText_Blended(font, "Hygiene", WHITE);
			break;
			
		case 6:
			pet->setBusiness(0);  // A ENLEVER QUAND LEVOLUTION DES STATS SERA FIXEE.
    		gaugeWidth = (gaugeBgWidth * pet->getBusiness()) / 100;
    		text = TTF_RenderText_Blended(font, "Petits besoins", WHITE);
			break;
			
		case 7:
			pet->setMood(50);  // A ENLEVER QUAND LEVOLUTION DES STATS SERA FIXEE.
    		gaugeWidth = (gaugeBgWidth * pet->getMood()) / 100;
    		text = TTF_RenderText_Blended(font, "Humeur", WHITE);
			break;
			
		case 8:
			pet->setAffection(0);  // A ENLEVER QUAND LEVOLUTION DES STATS SERA FIXEE.
    		gaugeWidth = (gaugeBgWidth * pet->getAffection()) / 100;
    		text = TTF_RenderText_Blended(font, "Affection", WHITE);
			break;
			
		case 9:
			pet->setSleep(0);  // A ENLEVER QUAND LEVOLUTION DES STATS SERA FIXEE.
    		gaugeWidth = (gaugeBgWidth * pet->getSleep()) / 100;
    		text = TTF_RenderText_Blended(font, "Fatigue", WHITE);
			break;
	}
	
    fillGauge = SDL_CreateRGBSurface(0, gaugeWidth, 25, 32, 0, 0, 0, 0);
    SDL_FillRect(fillGauge, NULL, SDL_MapRGB(screen->format,0,204,0));
    
    position.x = screen->w / 2 - gaugeBackground->w / 2;
    position.y = topMarge + 20;

    textPosition.x = position.x + gaugeBackground->w / 2 - text->w / 2;
    textPosition.y = position.y-2;
    SDL_BlitSurface(gaugeBackground, NULL, screen, &position);
    SDL_BlitSurface(fillGauge, NULL, screen, &position);
    SDL_BlitSurface(text, NULL, screen, &textPosition);
    
    position.y += gaugeBackground->h;
    
    TTF_Quit();
    return position.y;
    
}

void updateAll()
{
	
}

void updateLocation()
{
	
}

void updateThirst()
{
	
}

void updateHunger()
{
	
}

void updateTiredness()
{
	
}

void updateSocial()
{
	
}

void updateHygiene()
{
	
}

void updateBusiness()
{
	
}

void updateMood()
{
	
}

void updateAffection()
{
	
}

void updateDisease()
{
	
}
