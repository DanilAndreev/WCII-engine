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
#include "Enviroment.h"


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
	vector <EnviromentPreset> enviromentPresets;
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
	void refreshInputs();
	bool saveGame(string savename);
	Exitcode loadGame(string savename, bool showInfo);
	LiveUnitPreset* getUnitPreset(string name);
	EnviromentPreset* getEnviromentPreset(string name);
	ThreadId getGameAlifeTHREADDescriptor();
protected:
	void readUnits();
	void readSpells();
	void readBuildings();
	void readEnviroments();
	Exitcode ParseEnviroment(string filename, EnviromentPreset* writeTo);
	Exitcode ParseEnviroment(ParserOut input, EnviromentPreset* writeTo);
	Exitcode ParseUnit(string filename, LiveUnitPreset* writeTo);
	Exitcode ParseUnit(ParserOut input, LiveUnitPreset* writeTo);
	Exitcode readParseSpell(string filename);
	Exitcode readParseBuilding(string filename);
	int searchSpell(string name);
	int searchUnit(string name);
	int searchEnviroment(string name);
	int searchBuilding(string name);
	Exitcode addUnit(ParserOut data, vector<placeableData<LiveUnitPreset>>* arr);
	Exitcode addEnviroment(ParserOut data, vector<placeableData<EnviromentPreset>>* arr);
	Exitcode addField(ParserOut data, placeableData<FieldPreset> *writeTo);
	virtual void catchEvent(Command_c* command, bool showHelp);
protected:
	virtual void fillEventPatterns();
public: //GAME MASTER EVENTS
	static void exitGameCommand(Command_c* command, Eventable* oParent);
	static void stopThreadsCommand(Command_c* command, Eventable* oParent);
	static void saveGameCommand(Command_c* command, Eventable* oParent);
	static void loadGameCommand(Command_c* command, Eventable* oParent);
	static void refreshInputsCommand(Command_c* command, Eventable* oParent);
};

// exitgame
// stop threads {flags}
// save game [string:savename]
// load game [string:savename]


