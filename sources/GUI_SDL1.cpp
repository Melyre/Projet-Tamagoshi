#include "../headers/GUI.h"

GUI::GUI()
{
	SDL_Init(SDL_INIT_VIDEO); // Initialisation de la SDL
	
	/* Définition des curseurs système uniquement avec SDL2
	ARROW = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	POINTER = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	*/
	
	screen=SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); // Ouverture et paramètres de la fenêtre (SDL 1)
	
	//window = SDL_CreateWindow("Window SDL 2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0); //SDL2
	//screen = SDL_GetWindowSurface(window);//on crée la SDL_Window et on la convertit en SDL_Surface dans screen (SDL2)
}

GUI::~GUI()
{	
	clearButtons();
	
	//SDL_DestroyWindow(window); //nécessaire pour SDL2
	
	SDL_Quit(); // Arrêt de la SDL
	
	cout<<"SDL quittee !"<<endl;
}

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
            case SDL_QUIT:
                stop = true;
                return "quit";
                
            case SDL_MOUSEBUTTONUP:
            	pressedButton=getButtonName(event.button.x,event.button.y);
            	if(!pressedButton.empty()) return pressedButton;
            	
            /*case SDL_MOUSEMOTION:
            	hoverButton=getButtonName(event.button.x,event.button.y);
            	if(!hoverButton.empty()) switchCursor(POINTER);
            	else switchCursor(ARROW);*/
        }
    }
}

void GUI::addButton(SDL_Rect button, string buttonName)
{
	if(buttonName.empty())
	{
		cerr<<"Can't create a Button without a name or with an empty string name"<<endl;
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
		else cout<<endl;
	}
	return "";
}

void GUI::switchCursor(SDL_Cursor *cursor)
{
	if(SDL_GetCursor()!=cursor) SDL_SetCursor(cursor); //si le curseur actuel est différent du nouveau curseur on change
}

void GUI::displayMainMenu()
{
	cout<<"Debut display menu"<<endl;	
	
	SDL_Surface *text=NULL, *background=NULL;
    SDL_Rect position;
	
	if(TTF_Init() == -1)
	{
		cout<<"error in GUI::displayMenu, TTF_Init failed: "<<TTF_GetError()<<endl;
		return;
	}
	TTF_Font *font=NULL;
	font = TTF_OpenFont("../arial.ttf", 22);
	/*if(font == NULL);
	{
		cout<<"error in GUI::displayMenu, TTF_OpenFont failed: "<<TTF_GetError()<<endl;
		return;
	}*/
	
	text = TTF_RenderText_Blended(font, "Tamagotchi", WHITE);
	cout<<"Texte rendered !"<<endl;
	position.x = 250;
    position.y = 0;
    SDL_BlitSurface(text, NULL, screen, &position);
    
    text = TTF_RenderText_Blended(font, "Nouvelle partie", WHITE);
    position.x = 250;
    position.y = 75;
    SDL_BlitSurface(text, NULL, screen, &position);
	addButton(position,"newGame");
    
    text = TTF_RenderText_Blended(font, "Charger partie", WHITE);
    position.x = 250;
    position.y = 150;
    SDL_BlitSurface(text, NULL, screen, &position);
    addButton(position,"loadGame");
    
    text = TTF_RenderText_Blended(font, "Quitter", WHITE);
    position.x = 250;
    position.y = 225;
    SDL_BlitSurface(text, NULL, screen, &position);
    addButton(position,"quit");
    
    SDL_Flip(screen); //SDL 1
    //SDL_UpdateWindowSurface(window); //SDL2
	
	TTF_Quit();
	
	cout<<"Fin display menu"<<endl;	
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
