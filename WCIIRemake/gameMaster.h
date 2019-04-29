#pragma once
#include <vector>
#include <fstream>
#include <string>
#include "Spell.h"
#include "Obj.h"
#include "pch.h"


typedef int Exitcode;



class GameMaster : public Obj {
	vector <LiveUnit> creaturePresets;
//	vector <Building> buildingPresets;
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
	Exitcode readParseSpell(string filename);

};

