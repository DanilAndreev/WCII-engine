#pragma once
#include "Obj.h"
#include "pch.h"


class GameMaster : public Obj {
	vector <LiveUnit> creaturePresets;
	//vector <Building> buildingPresets;
	//vector <Spell> spellsPresets;
	DynArr players;
	string line;
	string beautyName;
	string fraction;
	char symbol;
	int width;
	int height;
	int health;
	int damage;
	int cooldown;
	int attackRadius;
	int speedDelay;
	int mana;
	char **spells;
	int cost;
	int eats;
	int productionTime;
	typedef vector<map<string, string>> parse;
	parse map;
	bool next_token(string & token);
	int check_token(string & token);
public:
	GameMaster();
	~GameMaster();
	vector<string>& split(const string & s, char delim, vector<string>& elems);

	vector<string> split(const string & s, char delim);

	void readUnits();
	void readSpells();
	void readBuildings();
	bool saveGame(vector<LiveUnit>& units);
	bool loadGame(vector<LiveUnit>& units);
};

