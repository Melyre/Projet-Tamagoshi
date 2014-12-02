#include "../headers/Disease.h"

Disease::Disease ()
{
	progression = 50.0;
	vet = false;
}

Disease::Disease (float p)
{
	progression = p;
	vet = false;
}

float Disease::getProgression ()
{
	return progression;
}

void Disease::setProgression (float p)
{
	progression = p;
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

float Disease::getInterval ()
{
	return interval;
}

void Disease::setInterval(float i)
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


