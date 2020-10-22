#include "pch.h"
#include "Building.h"

extern GameMaster* gameMaster;



BuildingPreset::BuildingPreset(string name, string beautyName, string fraction, char symbol, int width, int heigth, int health, int damage, int cooldown, int attackRadius, int mana, vector<string> spells, vector<string> production, int cost, int productionTime) {
	this->name = name;
	this->beautyName = beautyName;
	this->fraction = fraction;
	this->symbol = symbol;
	this->width = width;
	this->heigth = heigth;
	this->health = health;
	this->damage = damage;
	this->cooldown = cooldown;
	this->attackRadius = attackRadius;
	this->mana = mana;
	this->spells = spells;
	this->production = production;
	this->cost = cost;
	this->productionTime = productionTime;
}

BuildingPreset::~BuildingPreset() {
}

void BuildingPreset::print() {
	cout << "unit: " << name << ", beauty name: " << beautyName << endl;
	cout << "fraction: " << fraction << endl;
	cout << "symbol: " << symbol << endl;
	cout << "width: " << width << endl;
	cout << "heigth: " << heigth << endl;
	cout << "health: " << health << endl;
	cout << "damage: " << damage << endl;
	cout << "cooldown: " << cooldown << endl;
	cout << "attackRadius: " << attackRadius << endl;
	cout << "mana: " << mana << endl;
	cout << "spells: [";
	for (int i = 0; i < spells.size(); i++) {
		cout << spells[i] << " ";
	}
	cout << "]" << endl;
	cout << "production: [";
	for (int i = 0; i < production.size(); i++) {
		cout << production[i] << " ";
	}
	cout << "]" << endl;
	cout << "cost: " << cost << endl;
	cout << "productionTime: " << productionTime << endl;
	cout << endl;
}



Building::Building() {
}



Building::~Building() {
}

bool Building::classifyEvent(Command_c * command) {
	if (*command == "") {

	}

	return false;
}

void Building::operateEvent(Command_c * command) {
	classifyEvent(command);
}


//BUILDING COMMANDS(EVENTS)
bool Building::produce(Command_c * command) {
	if (true) {

	}
	return false;
}

