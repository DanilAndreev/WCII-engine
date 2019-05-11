#pragma once
#include <vector>
#include <fstream>
#include <string>
#include "Spell.h"
#include "LiveUnit.h"
#include "Building.h"
#include "Obj.h"
#include "pch.h"
#include "Exitcode.h"
#include "UnitInterpretor.h"
#include "GameAlifeThread.h"

template <class Tmpl>
struct placeableData {
	Tmpl preset;
	int x;
	int y;
	int team;
};


class GameMaster : public Obj {
private:	
	vector <LiveUnitPreset> creaturePresets;
	vector <BuildingPreset> buildingPresets;
	vector <SpellPreset> spellsPresets;
	DynArr players;
	Field* field;
	MScreen* scr;
	//---------------
	ThreadId GameAlifeTHREADDescriptor;
public:
	bool gameAlifeThreadIsRunning;
public:
	GameMaster();
	~GameMaster();
	vector <string> dirFilenames(string dirPath, string filetype);
	void readUnits();
	void readSpells();
	void readBuildings();
	bool saveGame();
	Exitcode loadGame(string savename);
	LiveUnitPreset* getUnitPreset(string name);
	ThreadId getGameAlifeTHREADDescriptor();
protected:
	Exitcode ParseUnit(string filename, LiveUnitPreset* writeTo);
	Exitcode ParseUnit(ParserOut input, LiveUnitPreset* writeTo);
	Exitcode readParseSpell(string filename);
	Exitcode readParseBuilding(string filename);
	int searchSpell(string name);
	int searchUnit(string name);
	int searchBuilding(string name);
	Exitcode addUnit(ParserOut data, vector<placeableData<LiveUnitPreset>>* arr);
	Exitcode addField(ParserOut data, placeableData<FieldPreset> *writeTo);
	bool classifyEvent(Command_c* command);
	virtual void operateEvent(Command_c* command);
protected:
	//GameMaster commands(events)
	bool exitgameEvent(Command_c* command);
	bool stopEvent(Command_c* command);
	bool loadEvent(Command_c* command);
};

