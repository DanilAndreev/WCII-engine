#pragma once

#include "pch.h"
#include "Screenable.h"
#include "Threadable.h"
#include "FastPath.h"
#include "CommandPatterns.h"
#include "MultiTeamSelector.h"
#include <ctime>
#include <stdlib.h>
#include "Eventable.h"
#include "Renderable.h"
#include "Placable.h"
#include "Obj.h"

class Unit : public Renderable, public Placable, public Obj, public MultiTeamSelector {
protected:
	Field* field;
	char value; //for debug
	int type;
	bool threadFlag;
	int health;
	int attackLength;
	int team; 
	string typeName;

	int width;
	int heigth;
	//TODO: add friend teams list
public:
	Unit(char value, int type, Field* field, int health, int team);
	Unit() : Unit('d', 1, NULL, 100, 0) {}
	virtual ~Unit();
	int getTeam();
	int getHealth();
	char getValue(); // возвращает символьное значение этого юнита(для проверки пока нет картинок и графики) 
	int getType(); // возвращает условный тип юнита(потом будет классификация на сухопутных, воздушных и морских юнитов)
	virtual void render(int layer); // отрисоваться(просчитаться)
	virtual void render();
	virtual void catchEvent(Command_c* command, bool showHelp);
protected:
	bool getDamage(int damage);
	virtual void stopAllThreads();
protected:
	virtual void fillEventPatterns();
public:	//UNIT EVENTS
	static void selectIdCommand(Command_c* command, Eventable* oParent);
	static void unselectIdCommand(Command_c* command, Eventable* oParent);
	static void damageIdCommand(Command_c* command, Eventable* oParent);
	static void getInfoIdCommand(Command_c* command, Eventable* oParent);
	static void echoIdCommand(Command_c* command, Eventable* oParent);
	static void getInfoUnitsCommand(Command_c* command, Eventable* oParent);
	static void getInfoTeamUnitsCommand(Command_c* command, Eventable* oParent);
	static void selectTeamCommand(Command_c* command, Eventable* oParent);
	static void renderLayerCommand(Command_c* command, Eventable* oParent);
};

// select team [int:team] id [int:id]
// unselect team [int:team] id [int::id]
// damage id [int:id] power [int:power]
// get info id [int::id]
// echo id [int:id] [quotes string:message]
// get info units
// get team [int:team] info units
// select team [int:team] {flags}
