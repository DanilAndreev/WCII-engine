#pragma once
#include "Obj.h"

struct SpellPreset {
	string name;
	string beautyName;
	string type;
	char symbol;
	int damage;
	int cooldown;
	int castCooldown;
	int attackRadius;
	int cost;
	int productionTime;
	SpellPreset(string name, string beautyName, string type, char symbol, int damage, int cooldown, int castCooldown, int attackRadius, int cost, int productionTime);
	~SpellPreset();
	void print();
};


class Spell : public Obj {
private:
	string beautyName;
	string type;
	char symbol;
	int damage;
	int cooldown;
	int castCooldown;
	int attackRadius;
	int cost;
	int productionTime;
public:
	Spell(string beautyName, string type, char symbol, int damage, int cooldown, int castCooldown, int attackRadius, int cost, int productionTime);
	Spell(SpellPreset preset);
	~Spell();
};

