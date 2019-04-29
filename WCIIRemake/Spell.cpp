#include "pch.h"
#include "Spell.h"


SpellPreset::SpellPreset(string name, string beautyName, string type, char symbol, int damage, int cooldown, int castCooldown, int attackRadius, int cost, int productionTime) {
	this->name = name;
	this->beautyName = beautyName;
	this->type = type;
	this->symbol = symbol;
	this->damage = damage;
	this->cooldown = cooldown;
	this->castCooldown = castCooldown;
	this->attackRadius = attackRadius;
	this->cost = cost;
	this->productionTime = productionTime;
}

SpellPreset::~SpellPreset() {
}

void SpellPreset::print() {
	cout << "Unit: " << name << ", beauty name: " << beautyName << endl;
	cout << "type: " << type << endl;
	cout << "symbol: " << symbol << endl;
	cout << "damage: " << damage << endl;
	cout << "cooldown: " << cooldown << endl;
	cout << "castCooldown: " << castCooldown << endl;
	cout << "attackRadius: " << attackRadius << endl;
	cout << "cost: " << cost << endl;
	cout << "productionTime: " << productionTime << endl;
}



Spell::Spell(string beautyName, string type, char symbol, int damage, int cooldown, int castCooldown, int attackRadius, int cost, int productionTime) {
	this->beautyName = beautyName;
	this->type = type;
	this->symbol = symbol;
	this->damage = damage;
	this->cooldown = cooldown;
	this->castCooldown = castCooldown;
	this->attackRadius = attackRadius;
	this->cost = cost;
	this->productionTime = productionTime;
}

Spell::Spell(SpellPreset preset) {
	this->beautyName = preset.beautyName;
	this->type = preset.type;
	this->symbol = preset.symbol;
	this->damage = preset.damage;
	this->cooldown = preset.cooldown;
	this->castCooldown = preset.castCooldown;
	this->attackRadius = preset.attackRadius;
	this->cost = preset.cost;
	this->productionTime = preset.productionTime;
}

Spell::~Spell() {
}
