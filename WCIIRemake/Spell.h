#pragma once
#include "Obj.h"

struct SpellPreset {
	string name;
	string beautyName;
	string type;
	char symbol;
	int damage;
	int heal;
	int cooldown;
	int castCooldown;
	int attackRadius;
	int cost;
	int productionTime;
	int targetType;
	int lifeTime;
	SpellPreset(string name, string beautyName, string type, char symbol, int damage, int cooldown, int castCooldown, int attackRadius, int cost, int productionTime, int heal, int targetType, int lifeTime);
	~SpellPreset();
	void print();
};


class Spell : public Obj {
private:
	string beautyName;
	string type;
	char symbol;
	int damage;
	int heal;
	int cooldown;
	int castCooldown;
	int attackRadius;
	int cost;
	int productionTime;
public:
	Spell(string name, string beautyName, string type, char symbol, int damage, int cooldown, int castCooldown, int attackRadius, int cost, int productionTime, int heal, int targetType, int lifeTime);
	Spell(SpellPreset preset);
	~Spell();
};

