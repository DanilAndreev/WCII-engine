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
#include "CommandPatterns.h"
#include "Eventable.h"
#include "EV_CScreen_FPS.h"
#include "CS_Selector.h"
template <class Tmpl>
struct placeableData {
	Tmpl preset;
	int x;
	int y;
	int team;
};


class GameMaster : public Obj{
protected:	
	vector <LiveUnitPreset> creaturePresets;
	vector <BuildingPreset> buildingPresets;
	vector <SpellPreset> spellsPresets;
	DynArr players;
	Field* field;
	//---------------
	ThreadId GameAlifeTHREADDescriptor;
public:
	EV_CScreen_FPS* scr;
	bool gameAlifeThreadIsRunning;
public:
	GameMaster();
	~GameMaster();
	vector <string> dirFilenames(string dirPath, string filetype);
	void readUnits();
	void readSpells();
	void readBuildings();
	bool saveGame(string savename);
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
	virtual void catchEvent(Command_c* command, bool showHelp);
protected:
	virtual void fillEventPatterns();
public: //GAME MASTER EVENTS
	static void exitGameCommand(Command_c* command, Eventable* oParent);
	static void stopThreadsCommand(Command_c* command, Eventable* oParent);
	static void saveGameCommand(Command_c* command, Eventable* oParent);
	static void loadGameCommand(Command_c* command, Eventable* oParent);
};

// exitgame
// stop threads {flags}
// save game [string:savename]
// load game [string:savename]


