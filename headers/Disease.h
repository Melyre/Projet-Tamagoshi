#include <iostream>
#include <string>

using namespace std;

class Disease 
{
public:
	int getProgression ();
	void setProgression (int progression);
	bool getVet ();
	void setVet (bool vet);
	int getInterval ();
	void setInterval (int interval);
	int getLastHeal ();
	void setLastHeal (int lastHeal);
private:
	int progression;
	bool vet;
	int interval;
	int lastHeal;
};
