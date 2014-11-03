#include "../headers/Tamagotchi.h"

Tamagotchi::Tamagotchi()
{
	
}

Tamagotchi::Tamagotchi(string race)
{
	setRace(race);
}

Tamagotchi::Tamagotchi(string race, string name)
{
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

int Tamagotchi::getThirst()
{
	return thirst;
}

void Tamagotchi::setThirst(int thirst)
{
	this->thirst=thirst;
}

int Tamagotchi::getHunger()
{
	return hunger;
}

void Tamagotchi::setHunger(int hunger)
{
	this->hunger=hunger;
}

int Tamagotchi::getTiredness()
{
	return tiredness;
}

void Tamagotchi::setTiredness(int tiredness)
{
	this->tiredness=tiredness;
}

int Tamagotchi::getSocial()
{
	return social;
}

void Tamagotchi::setSocial(int social)
{
	this->social=social;
}

int Tamagotchi::getHygiene()
{
	return hygiene;
}

void Tamagotchi::setHygiene(int hygiene)
{
	this->hygiene=hygiene;
}

int Tamagotchi::getBusiness()
{
	return business;
}

void Tamagotchi::setBusiness(int business)
{
	this->business=business;
}

int Tamagotchi::getMood()
{
	return mood;
}

void Tamagotchi::setMood(int mood)
{
	this->mood=mood;
}

int Tamagotchi::getAffection()
{
	return affection;
}

void Tamagotchi::setAffection(int affection)
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

