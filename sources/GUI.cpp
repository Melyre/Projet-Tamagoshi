#include "../headers/GUI.h"

GUI::GUI()
{
	SDL_Init(SDL_INIT_VIDEO); // Initialisation de la SDL
	
	SDL_Color BLACK = {0, 0, 0};
	SDL_Color WHITE = {255, 255, 255};
	
	SDL_Surface *screen=SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); // Ouverture de la fenêtre
	SDL_Surface *text=NULL, *background=NULL;
    SDL_Rect position;
	
	TTF_Init();
	TTF_Font *font=NULL;
	font = TTF_OpenFont("../arial.ttf", 22);
	
	
	text = TTF_RenderText_Blended(font, "Tamagotchi", WHITE);
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
    
    SDL_Flip(screen);
	
	TTF_Quit();
}

GUI::~GUI()
{
	cout<<"GUI destruction... ";
	clearButtons();
	SDL_Quit(); // Arrêt de la SDL
	cout<<"SDL quittee !"<<endl;
}

string GUI::waitEvent()
{
    int stop = false;
    SDL_Event event;
 
    while (!stop)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                stop = true;
                return "quit";
                
            case SDL_MOUSEBUTTONUP:
            	string pressedButton=getButtonName(event.button.x,event.button.y);
            	if(!pressedButton.empty()) return pressedButton;
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
	cout<<"< Event: Clic ("<<x<<", "<<y<<")"<<endl;
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
