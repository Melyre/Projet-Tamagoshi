#include "../headers/Disease.h"

Disease::Disease ()
{
	progression = 50;
	vet = false;
}

Disease::Disease (int p)
{
	progression = p;
	vet = false;
}

int Disease::getProgression ()
{
	return progression;
}

void Disease::setProgression (int p)
{
	if(p > 0 && p < 100)progression = p;
	else cerr << "Veuillez choisir une progression entre 0 et 100." << endl;
}

bool Disease::getVet ()
{
	if(vet)return true;
	return false;
}

void Disease::setVet (bool v)
{
	vet = v;
}

void Disease::defineDiseaseRandomly ()
{
	if(!vet)return;

	int i = (rand()+6)%24 ;
	interval = i * 3600;
}

int Disease::getInterval ()
{
	return interval;
}

void Disease::setInterval(int i)
{
	interval = i;
}

time_t Disease::getLastHeal ()
{
	return lastHeal;
}

void Disease::setLastHeal (time_t lH)
{
	lastHeal = lH;
}

void Disease::setLastHeal (int lH)
{
	lastHeal = lH;
}


