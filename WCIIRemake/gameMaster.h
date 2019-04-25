#pragma once
#include "Obj.h"
#include "pch.h"

#include <map>


class GameMaster : public Obj {
	vector <LiveUnit> creaturePresets;
	//vector <Building> buildingPresets;
	//vector <Spell> spellsPresets;
	DynArr players;
	string line; //get line from file
	string beautyName; // name of person
	string fraction;
	char symbol; // symbol of pers
	int width;
	int height;
	int health;
	int damage;
	int cooldown;
	int attackRadius;
	int speedDelay;
	int mana;
	vector<string> spells; // spells of pers
	int cost;
	int eats;
	int productionTime;
	typedef vector<map<string, string>> parse; // idea parse line into vector of map of strings(like BeautyName:, Berserker)
	parse map;
	bool next_token(string & token); // function for splitting line into parts
	int check_token(string & token); // check what token means
public:
	GameMaster();
	~GameMaster();
	vector<string>& split(const string & s, char delim, vector<string>& elems); //another function for splitting into vector of strings

	vector<string> split(const string & s, char delim);

	void readUnits();
	//void readSpells();
	void readBuildings();
	bool saveGame(vector<LiveUnit>& units);
	bool loadGame(vector<LiveUnit>& units);
};

