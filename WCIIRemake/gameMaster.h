#pragma once
#include "Obj.h"


class GameMaster : public Obj {
	vector <LiveUnit> creaturePresets;
	vector <Building> buildingPresets;
	//vector <Spell> spellsPresets;
	DynArr players; 

public:
	GameMaster();
	~GameMaster();
	void readUnits();
	void readSpells();
	void readBuildings();
	bool saveGame();
	bool loadGame();
};

