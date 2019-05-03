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




class GameMaster : public Obj {
private:
	vector <LiveUnitPreset> creaturePresets;
	vector <BuildingPreset> buildingPresets;
	vector <SpellPreset> spellsPresets;
	DynArr players;
public:
	GameMaster();
	~GameMaster();
	vector <string> dirFilenames(string dirPath);
	void readUnits();
	void readSpells();
	void readBuildings();
	bool saveGame();
	bool loadGame();
	LiveUnitPreset* getUnitPreset(string name);
private:
	Exitcode readParseUnit(string filename);
	Exitcode readParseSpell(string filename);
	Exitcode readParseBuilding(string filename);
	int searchSpell(string name);
	int searchUnit(string name);
	int searchBuilding(string name);
};

