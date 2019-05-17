#pragma once

#include "pch.h"
#include "Screenable.h"
#include "Threadable.h"
#include "FastPath.h"
#include "CommandPatterns.h"
#include <ctime>
#include <stdlib.h>

class Unit : public Screenable, public CommandPatterns {
protected:
	Field* field;
	char value; //for debug
	int type;
	bool threadFlag;
	int health;
	int attackLength;
	int team; 
	string typeName;
	//TODO: add friend teams list
public:
	Unit(char value, int type, Field* field, int health, int team);
	Unit() : Unit('d', 1, NULL, 100, 0) {}
	virtual ~Unit();
	int getTeam();
	int getHealth();
	char getValue(); // возвращает символьное значение этого юнита(для проверки пока нет картинок и графики) 
	int getType(); // возвращает условный тип юнита(потом будет классификация на сухопутных, воздушных и морских юнитов)
	virtual void render(); // отрисоваться(просчитаться)
	bool classifyEvent(Command_c* command);
	virtual void operateEvent(Command_c* command);
protected:
	bool getDamage(int damage);
	virtual void stopAllThreads();
	virtual void fillCommandPatterns();
	bool operateConsoleCommand(Command_c * command, bool showHelp);
protected:
	//UNIT COMMANDS(EVENTS)
	bool selectEvent(Command_c* command);
	bool echoEvent(Command_c* command);
	bool damageEvent(Command_c* command);
	bool getInfoEvent(Command_c * command);

protected:
	void selectIdCommand(Command_c* command, Obj* oParent);
	void damageIdCommand(Command_c* command, Obj* oParent);
	void getInfoIdCommand(Command_c* command, Obj* oParent);
	void echoIdCommand(Command_c* command, Obj* oParent);
};

