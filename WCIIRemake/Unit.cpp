#include "pch.h"
#include "Unit.h"

extern Controller* gameController;
extern ThreadDescriptor* gameThreads;

Unit::Unit(char value, int type, Field* field, int health, int team,  int attackLength) {
	this->team = team;
	this->attackLength = attackLength;
	this->value = value;
	this->field = field;
	this->type = type;
	this->threadFlag = false;
	this->health = health;
}


Unit::~Unit() {

}

int Unit::getTeam()
{
	return this->team;
}

int Unit::getHealth()
{
	return this->health;
}

int Unit::getType() {
	return this->type;
}

char Unit::getValue() {
	return value;
}





void Unit::render() {
	if (scr != NULL) {
		scr->putToBuff(this->cords, this->value);
	}
}

bool Unit::classifyEvent(Command_c* command) {
	if (*command == "select") {
		return selectEvent(command);
	}


	if (*command == "echo" && this->selected) {
		return echoEvent(command);
	}

	if (*command == "damage") {
		return damageEvent(command);
	}

	if (*command == "getInfo") {
		return getInfoEvent(command);
	}

	return false;
}

void Unit::operateEvent(Command_c* command)
{
	classifyEvent(command);
}


bool Unit::getDamage(int damage) {
	if (health > 0) {
		this->health -= damage;
		Beep(500, 70);
		if (this->health < 0) {
			health = 0;
			this->value = '#';
			stopAllThreads();
		}
		return true;
	}
	else {
		this->value = '#';
		stopAllThreads();
	}
	return false;

}

void Unit::stopAllThreads() {
}

//UNIT COMMANDS(EVENTS)
bool Unit::selectEvent(Command_c* command) {
	if (command->args.size() == 2) {
		if (command->args[1].first == "all") {
			this->selected = true;
			cout << "selected unit '" << this->value << "', id : " << this->getId() << endl;
			return true;
		}
		if (command->args[1].second == "number") {
			if (stoi(command->args[1].first) == this->getId()) {
				this->selected = true;
				cout << "selected unit '" << this->value << "', id : " << this->getId() << endl;
				return true;
			}
		}
	}
	if (command->args.size() > 1) {
		for (int i = 1; i < command->args.size(); i++) {
			if (command->args[i].first[0] == this->value) {
				this->selected = true;
				cout << "selected unit '" << this->value << "', id : " << this->getId() << endl;
				return true;
			}
		}
		this->selected = false;
		return true;
	}
	return false;
}

bool Unit::echoEvent(Command_c* command) {
	if (command->args.size() > 1) {
		string msg;
		for (int i = 1; i < command->args.size(); i++) {
			msg += command->args[i].first + " ";
		}
		cout << "Unit " << value << " say: " << msg << endl;
		return true;
	}
	return false;
}

bool Unit::damageEvent(Command_c* command) {
	if (command->args.size() == 3) {
		if (command->args[1].first[0] == this->value && command->args[2].second == "number") {
			getDamage(stoi(command->args[2].first));
		}
	}
	return false;
}

bool Unit::getInfoEvent(Command_c* command) {
	if (command->args.size() >= 3) {
		if (command->args[1].second == "number" && command->args[2].second == "number") {
			if (stoi(command->args[1].first) == this->cords.x && stoi(command->args[2].first) == this->cords.y) {
				command->data.push_back(eventReturnData(this->id, this->cords));
				if (command->args.size() >= 5) {
					if (command->args[3].first == "-display") {
						for (int i = 4; i < command->args.size(); i++) {
							if (command->args[i].first == "id") {
								cout << "id : " << this->id << endl;
							}
							if (command->args[i].first == "health") {
								cout << "health : " << this->health << endl;
							}
							if (command->args[i].first == "cords") {
								cout << "cords : " << this->cords.x << " " << this->cords.y << endl;
							}
						}
					}
				}
				return true;
			}
		}
	}

	if (command->args.size() >= 2) {
		if (command->args[1].second == "number") {
			if (stoull(command->args[1].first) == this->id) {
				command->data.push_back(eventReturnData(this->id, this->cords));
				if (command->args.size() >= 4) {
					if (command->args[2].first == "-display") {
						for (int i = 3; i < command->args.size(); i++) {
							if (command->args[i].first == "id") {
								cout << "id : " << this->id << endl;
							}
							if (command->args[i].first == "health") {
								cout << "health : " << this->health << endl;
							}
							if (command->args[i].first == "cords") {
								cout << "cords : " << this->cords.x << " " << this->cords.y << endl;
							}
						}
					}
				}
				return true;
			}
		}
	}


	return false;
}
