#pragma once
#include "Unit.h"


class Building : public Unit {
protected:
	queue <Unit> productionQueue;
public:
	Building(char value, int type, Field* field, int health, int team, int attackLength) : Unit(value, type, field, health, team, attackLength){}
	Building();
	~Building();
	bool classifyEvent(Command_c* command);
	virtual void operateEvent(Command_c* command);
	//BUILDING COMMANDS(EVENTS)
	bool produce(Command_c* command);
};

