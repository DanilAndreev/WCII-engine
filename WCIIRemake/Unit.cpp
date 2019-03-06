#include "pch.h"
#include "Unit.h"

extern Controller* gameController;

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

bool Unit::classifyEvent(Command_c command) {
	if (command == "select") {
		return selectEvent(command);
	}


	if (command == "echo" && this->selected) {
		return echoEvent(command);
	}

	if (command == "damage") {
		return damageEvent(command);
	}

	return false;
}

/*
void Unit::threadFunction() {
}
*/

void Unit::operateEvent(Command_c command)
{
	classifyEvent(command);
}


bool Unit::getDamage(int damage) {
	if (health > 0) {
		this->health -= damage;
		if (this->health < 0) {
			health = 0;
			this->value = '#';
		}
		return true;
	}
	else {
		this->value = '#';
	}
	return false;
}

/*

void Unit::attack() {
	DynArr* fmembers = field->getMembers();
	for (int i = 0; i < fmembers->count(); i++) {
		Unit* cunit = (Unit*)(fmembers->get(i));
		float curDist = this->cords.lineLength(this->cords, cunit->getCord());
		if (curDist <= this->attackLength) {
			Command_c dEvent;
			pair<string, string> temp;

			temp.first = "damage";
			temp.second = "command";
			dEvent.args.push_back(temp);

			temp.first = cunit->getValue();
			temp.second = "command";
			dEvent.args.push_back(temp);

			temp.first = to_string(50); // add unit powerful
			temp.second = "number";
			dEvent.args.push_back(temp);


			gameController->addEventToQueue(dEvent);
			break;
		}
	}
}

*/

//UNIT COMMANDS(EVENTS)
bool Unit::selectEvent(Command_c command) {
	if (command.args.size() == 2) {
		if (command.args[1].first == "all") {
			this->selected = true;
			return true;
		}
	}
	if (command.args.size() > 1) {
		for (int i = 1; i < command.args.size(); i++) {
			if (command.args[i].first[0] == this->value) {
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

bool Unit::echoEvent(Command_c command) {
	if (command.args.size() > 1) {
		string msg;
		for (int i = 1; i < command.args.size(); i++) {
			msg += command.args[i].first + " ";
		}
		cout << "Unit " << value << " say: " << msg << endl;
		return true;
	}
	return false;
}


bool Unit::damageEvent(Command_c command) {
	if (command.args.size() == 3) {
		if (command.args[1].first[0] == this->value && command.args[2].second == "number") {
			getDamage(stoi(command.args[2].first));
		}
	}
	return false;
}

