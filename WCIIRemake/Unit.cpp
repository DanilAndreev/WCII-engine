#include "pch.h"
#include "Unit.h"

extern Controller* gameController;
extern ThreadDescriptor* gameThreads;

/*
Unit::Unit(Unit** field) {
	this->field = field;
}


Unit::Unit() {
	Unit(NULL);
}
*/
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

	return false;
}

/*
void Unit::threadFunction() {
}
*/

void Unit::operateEvent(Command_c* command)
{
	classifyEvent(command);
}


bool Unit::getDamage(int damage) {
	if (health > 0) {
		this->health -= damage;
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
			cout << "selected unit '" << this->value << "'" << endl;
			return true;
		}
	}
	if (command->args.size() > 1) {
		for (int i = 1; i < command->args.size(); i++) {
			if (command->args[i].first[0] == this->value) {
				cout << "selected unit '" << this->value << "'" << endl;
				this->selected = true;
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