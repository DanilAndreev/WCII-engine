#pragma once
#include "Unit.h"

struct BuildingPreset {
public:
	string name;
	string beautyName;
	string fraction;
	char symbol;
	int width;
	int heigth;
	int health;
	int damage;
	int cooldown;
	int attackRadius;
	int mana;
	vector <string> spells;
	vector <string> production;
	int cost;
	int productionTime;
public:
	BuildingPreset(string name, string beautyName, string fraction, char symbol, int width, int heigth, int health, int damage, int cooldown, int attackRadius, int mana, vector <string> spells, vector <string> production, int cost, int productionTime);
	~BuildingPreset();
	void print();
};


class Building : public Unit {
protected:
	queue <Unit> productionQueue;
public:
	Building(char value, int type, Field* field, int health, int team) : Unit(value, type, field, health, team){}
	Building();
	~Building();
	bool classifyEvent(Command_c* command);
	virtual void operateEvent(Command_c* command);
	//BUILDING COMMANDS(EVENTS)
	bool produce(Command_c* command);
};

