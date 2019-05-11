#include "pch.h"
#include "Field.h"

extern Console* defaultConsole;
extern GameMaster* gameMaster;


Field::Field(int width, int heigth) {
	fieldLen = width * heigth;

	this->width = width;
	this->heigth = heigth;
	members = new DynArr();
}



Field::~Field() {
	delete members;
}

DynArr* Field::getMembers() {
	return members;
}


void Field::freeElements() {
	members->freeItems();
}

bool Field::checkFree(cordScr cords, int type) {
	if (cords.x >= this->width || cords.y >= this->heigth) {
		return false;
	}
	for (int i = 0; i < members->count(); i++) {
		Unit* unit = (Unit*)(members->get(i));
		if (unit->getCord() == cords && unit->getType() == type) {
			return false;
		}
	}
	return true;
}





int Field::setCell(cordScr cords, Unit* target) {
	if (members->search(target) == -1) {
		if (checkFree(cords, target->getType())) {
			target->setup(cords, 1, 1, this->scr);
			members->add(target);
			return 1;
		}
	}
	return 0;
}


int Field::changeCell(cordScr cordsNew, Unit* target) {
	int foundInd = members->search(target);
	if (foundInd > -1) {
		if (checkFree(cordsNew, target->getType())) {
			target->setCord(cordsNew);
			return 1;
		}
	}
	return 0;
}

void Field::render() {

	for (int i = 0; i < members->count(); i++) {
		((Screenable*)(members->get(i)))->render();
	}
}

bool Field::classifyEvent(Command_c* command) {
	if (*command == "select") {

	}
	if (*command == "spawn") {
		return spawn(command);
	}

	return false;
}

void Field::operateEvent(Command_c* command) {
	for (int i = 0; i < members->count(); i++) {
		members->get(i)->operateEvent(command);
	}
	classifyEvent(command);
}

//Field commands(Events)

//spawn unit 10(x) 10(y) 1(team) 100(health) 100(attackLen) 1(type) v(value) 1000(cooldown) 100
//spawn building 10(x) 10(y) 1(team) 100(health) 1(type) v(value) 
bool Field::spawn(Command_c* command) {
	if (command->args.size() == 10) {
		if (command->args[1].first == "unit") {
			if (command->args[2].second == "number" && command->args[3].second == "number" && command->args[4].second == "number" && command->args[5].second == "number" && command->args[6].second == "number" && command->args[7].second == "number" && command->args[8].second == "command" && command->args[9].second == "number" && command->args[10].second == "number" && command->args[11].second == "number") {
				int x = stoi(command->args[2].first);
				int y = stoi(command->args[3].first);
				int team = stoi(command->args[4].first);
				int health = stoi(command->args[5].first);
				int attackLength = stoi(command->args[6].first);
				int type = stoi(command->args[7].first);
				int value = command->args[8].first[0];
				time_t cooldown = (time_t)stoi(command->args[9].first);
				time_t moveSpeed = (time_t)stoi(command->args[10].first);
				int attackPower = stoi(command->args[11].first);
				LiveUnit* unit = new LiveUnit(value, type, this, health, team, attackLength, cooldown, moveSpeed, attackPower);
				this->setCell(cordScr(x, y), (Unit*)unit);
				return true;
			}
		}
	}
	if (command->args.size() == 8) {
		if (command->args[1].first == "building") {
			if (command->args[2].second == "number" && command->args[3].second == "number" && command->args[4].second == "number" && command->args[5].second == "number" && command->args[6].second == "number" && command->args[7].second == "command") {
				int x = stoi(command->args[2].first);
				int y = stoi(command->args[3].first);
				int team = stoi(command->args[4].first);
				int health = stoi(command->args[5].first);
				int type = stoi(command->args[6].first);
				int value = command->args[7].first[0];
				Building* unit = new Building(value, type, this, health, team);
				this->setCell(cordScr(x, y), (Unit*)unit);
				return true;
			}
		}
	}
	// spawn team 1 unit berserker 10 10
	if (command->args.size() == 7) {
		if (command->args[1].first == "team" && command->args[2].second == "number" && command->args[3].second == "command" && command->args[4].second == "command" && command->args[5].second == "number" && command->args[6].second == "number") {
			if (command->args[3].first == "unit") {
				LiveUnitPreset* preset = gameMaster->getUnitPreset(command->args[4].first);
				if (preset) {
					int x = stoi(command->args[5].first);
					int y = stoi(command->args[6].first);
					int team = stoi(command->args[2].first);
					LiveUnit* unit = new LiveUnit(*preset, this, team);
					this->setCell(cordScr(x, y), (Unit*)unit);
				}
			}
		}
	}
	return false;
}
