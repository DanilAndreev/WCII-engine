#pragma once
#include <vector>
#include <fstream>
#include <string>
#include "Spell.h"
#include "LiveUnit.h"
#include "Building.h"
#include "Obj.h"
#include "pch.h"


typedef int Exitcode;



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
private:
	Exitcode readParseUnit(string filename);
	Exitcode readParseSpell(string filename);
	Exitcode readParseBuilding(string filename);

};

