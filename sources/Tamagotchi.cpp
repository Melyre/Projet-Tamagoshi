#include "../headers/Tamagotchi.h"

Tamagotchi::Tamagotchi()
{
	disease=NULL;
}

Tamagotchi::Tamagotchi(string race)
{
	disease=NULL;
	setRace(race);
}

Tamagotchi::Tamagotchi(string race, string name)
{
	disease=NULL;
	setRace(race);
	setName(name);
}

Tamagotchi::~Tamagotchi()
{
	delete disease;
}

string Tamagotchi::getRace()
{
	return race;
}

void Tamagotchi::setRace(string race)
{
	this->race=race;
}

string Tamagotchi::getName()
{
	return name;
}

void Tamagotchi::setName(string name)
{
	this->name=name;
}

float Tamagotchi::getThirst()
{
	return thirst;
}

void Tamagotchi::setThirst(float thirst)
{
    if(thirst<=0) this->thirst=0;
    else if(thirst>MAX_GAUGE_VALUE) this->thirst=MAX_GAUGE_VALUE;
	else this->thirst=thirst;
}

float Tamagotchi::getHunger()
{
	return hunger;
}

void Tamagotchi::setHunger(float hunger)
{
    if(hunger<=0) this->hunger=0;
    else if(hunger>MAX_GAUGE_VALUE) this->hunger=MAX_GAUGE_VALUE;
	else this->hunger=hunger;
}

float Tamagotchi::getTiredness()
{
	return tiredness;
}

void Tamagotchi::setTiredness(float tiredness)
{
    if(tiredness<=0) this->tiredness=0;
    else if(tiredness>MAX_GAUGE_VALUE) this->tiredness=MAX_GAUGE_VALUE;
	else this->tiredness=tiredness;
}

float Tamagotchi::getSocial()
{
	return social;
}

void Tamagotchi::setSocial(float social)
{
    if(social<=0) this->social=0;
    else if(social>MAX_GAUGE_VALUE) this->social=MAX_GAUGE_VALUE;
	else this->social=social;
}

float Tamagotchi::getHygiene()
{
	return hygiene;
}

void Tamagotchi::setHygiene(float hygiene)
{
    if(hygiene<=0) this->hygiene=0;
    else if(hygiene>MAX_GAUGE_VALUE) this->hygiene=MAX_GAUGE_VALUE;
	else this->hygiene=hygiene;
}

float Tamagotchi::getBusiness()
{
	return business;
}

void Tamagotchi::setBusiness(float business)
{
    if(business<=0) this->business=0;
    else if(business>MAX_GAUGE_VALUE) this->business=MAX_GAUGE_VALUE;
	else this->business=business;
}

float Tamagotchi::getMood()
{
	return mood;
}

void Tamagotchi::setMood(float mood)
{
    if(mood<=0) this->mood=0;
    else if(mood>MAX_GAUGE_VALUE) this->mood=MAX_GAUGE_VALUE;
	else this->mood=mood;
}

float Tamagotchi::getAffection()
{
	return affection;
}

void Tamagotchi::setAffection(float affection)
{
	this->affection=affection;
}

Disease *Tamagotchi::getDisease()
{
	return disease;
}

void Tamagotchi::setDisease(Disease *disease)
{
	this->disease=disease;
}

bool Tamagotchi::getSleep()
{
	return sleep;
}

void Tamagotchi::setSleep(bool sleep)
{
	this->sleep=sleep;
}

int Tamagotchi::getLife()
{
	return life;
}

void Tamagotchi::setLife(int life)
{
    if(life<=0) this->life=0; //si la vie est à 0 le Tamagotchi meurt
    if(life>MAX_GAUGE_VALUE) this->life=MAX_GAUGE_VALUE;
	else this->life=life;
}

