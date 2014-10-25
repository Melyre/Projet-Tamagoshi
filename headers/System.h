#include <iostream>
#include <string>

using namespace std;

class System 
{
public:
	void mainMenu ();
	void optionMenu ();
	void backToMenu ();
	string getWeather ( );
	string getLocation ();
	*Tamagotchi getPet ();
	void setEndProgram (bool end);
	void setEndGame (bool end);
	void feed (int n);
	void giveDrink (int n);
	void wakeUp ( );
	void heal (int n);
	void wash (int n);
	void playMini ( );
	void goOut ();
	void doBusiness (int n);
private:
	void loadGame ();
	void runGame ();
	void update (string lastTime);
	void saveGame ();
	void newGame ();
	void deleteSave ();
	void update ();
	*GUI interface;
	*Tamagotchi pet;
	string location;
	string saveName;
	int timeSpeed;
	string weather;
	bool endGame;
	bool endProgram;
};
