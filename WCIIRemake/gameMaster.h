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

template <class Tmpl>
struct fieldableData {
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
private:
	Exitcode ParseUnit(string filename, LiveUnitPreset* writeTo);
	Exitcode ParseUnit(ParserOut input, LiveUnitPreset* writeTo);
	Exitcode readParseSpell(string filename);
	Exitcode readParseBuilding(string filename);
	int searchSpell(string name);
	int searchUnit(string name);
	int searchBuilding(string name);
	Exitcode addUnit(ParserOut data, vector<fieldableData<LiveUnitPreset>>* arr);
};

