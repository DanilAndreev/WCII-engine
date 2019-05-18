#include "pch.h"
#include "Unit.h"

extern Controller* gameController;
extern ThreadDescriptor* gameThreads;
extern Console* defaultConsole;

Unit::Unit(char value, int type, Field* field, int health, int team) {
	this->fillCommandPatterns();
	this->team = team;
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
		cordScr shift;
		if (field) {
			shift = this->field->getCord();
		}
		scr->putToBuff(this->cords + shift, this->value);
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

void Unit::operateEvent(Command_c* command) {
//	classifyEvent(command);
	operateConsoleCommand(command, false);
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

void Unit::fillCommandPatterns() {
	const ConsoleCommandPattern selectIdPattern(
		"select team input_number id input_number",
		"selectIdPattern",
		"select team [int:team] id [int::id]",
		Unit::selectIdCommand);
	const ConsoleCommandPattern unselectIdPattern(
		"unselect team input_number id input_number",
		"unselectIdPattern",
		"unselect team [int:team] id [int::id]",
		Unit::unselectIdCommand);
	const ConsoleCommandPattern selectTeamPattern(
		"select team input_number",
		"selectTeamPattern",
		"select team [int:team] {flags}",
		Unit::selectTeamCommand);
	const ConsoleCommandPattern dammageIdPattern(
		"damaage id input_number power input_number",
		"damageIdPattern",
		"damage id [int:id] power [int::power]",
		Unit::damageIdCommand);
	const ConsoleCommandPattern getInfoIdPattern(
		"get info id input_number",
		"getInfoIdPattern",
		"get info id [int::id]",
		Unit::getInfoIdCommand);
	const ConsoleCommandPattern echoIdPattern(
		"echo id input_number input_command",
		"echoIdPattern",
		"echo id [int:id] [quotes string:message]",
		Unit::echoIdCommand);
	const ConsoleCommandPattern getInfoUnitsPattern(
		"get info units",
		"getInfoUnitsPattern",
		"get info units",
		Unit::getInfoUnitsCommand);
	const ConsoleCommandPattern getInfoTeamUnitsPattern(
		"get team input_number info units",
		"getInfoTeamUnitsPattern",
		"get team [int:team] info units",
		Unit::getInfoTeamUnitsCommand);

	this->commandPatterns.push_back(selectIdPattern);
	this->commandPatterns.push_back(unselectIdPattern);
	this->commandPatterns.push_back(selectTeamPattern);
	this->commandPatterns.push_back(dammageIdPattern);
	this->commandPatterns.push_back(getInfoIdPattern);
	this->commandPatterns.push_back(echoIdPattern);
	this->commandPatterns.push_back(getInfoUnitsPattern);
	this->commandPatterns.push_back(getInfoTeamUnitsPattern);
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
		if (command->args[1].second == "number" && command->args[2].second == "number") {
			if (stoi(command->args[1].first) == this->id) {
				getDamage(stoi(command->args[2].first));
			}
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


// select team [int:team] id [int:id]
void Unit::selectIdCommand(Command_c * command, CommandPatterns* oParent) {
	Unit* parent = dynamic_cast<Unit*>(oParent);
	if (!parent) {
		return;
	}
	ID input_id = 0;
	int input_team = 0;
	try {
		input_team = stoi(command->args[2].first);
		input_id = stoull (command->args[4].first);
	}
	catch (...) {
		return;
	}
	if (input_id == parent->id) {
		parent->select(input_team);
		cout << "selected unit: " << parent->value << " , ID : " << parent->id << endl;
	}
}

// unselect team [int:team] id [int::id]
void Unit::unselectIdCommand(Command_c* command, CommandPatterns* oParent) {
	Unit* parent = dynamic_cast<Unit*>(oParent);
	if (!parent) {
		return;
	}
	ID input_id = 0;
	int input_team = 0;
	try {
		input_team = stoi(command->args[2].first);
		input_id = stoull(command->args[4].first);
	}
	catch (...) {
		return;
	}
	if (input_id == parent->id) {
		parent->unselect(input_team);
	}
}

// damage id [int:id] power [int:power]
void Unit::damageIdCommand(Command_c * command, CommandPatterns* oParent) {
	Unit* parent = dynamic_cast<Unit*>(oParent);
	if (!parent) {
		return;
	}
	ID input_id = 0;
	int input_damage = 0;
	try {
		input_id = stoull(command->args[2].first);
		input_damage = stoi(command->args[4].first);
	}
	catch (...) {
		return;
	}
	if (input_id == parent->id) {
		parent->getDamage(input_damage);
	}
}

// get info id [int::id]
void Unit::getInfoIdCommand(Command_c * command, CommandPatterns* oParent) {
	Unit* parent = dynamic_cast<Unit*>(oParent);
	if (!parent) {
		return;
	}
	ID input_id = 0;
	try {
		input_id = stoull(command->args[2].first);
	}
	catch (...) {
		return;
	}
	if (parent->id == input_id) {
		string temp;
		temp += parent->value;
		command->data.push_back(eventReturnData(parent->id, parent->cords, parent->className, parent->health, temp, NULL, parent->team));
	}
}


// echo id [int:id] [quotes string:message]
void Unit::echoIdCommand(Command_c * command, CommandPatterns* oParent) {
	Unit* parent = dynamic_cast<Unit*>(oParent);
	if (!parent) {
		return;
	}
	ID input_id = 0;
	try {
		input_id = stoull(command->args[2].first);
	}
	catch (...) {
		return;
	}
	if (parent->id == input_id) {
		defaultConsole->message(string("Unit ") + to_string(parent->id) + " says: " + command->args[3].first);
	}
}

// get info units
void Unit::getInfoUnitsCommand(Command_c* command, CommandPatterns* oParent) {
	Unit* parent = dynamic_cast<Unit*>(oParent);
	if (!parent) {
		return;
	}
	string temp;
	temp += parent->value;
	command->data.push_back(eventReturnData(parent->id, parent->cords, parent->className, parent->health, temp, NULL, parent->team));
}

// get team [int:team] info units
void Unit::getInfoTeamUnitsCommand(Command_c* command, CommandPatterns* oParent) {
	Unit* parent = dynamic_cast<Unit*>(oParent);
	if (!parent) {
		return;
	}
	int input_team = 0;
	try {
		input_team = stoi(command->args[2].first);
	}
	catch (...) {
		return;
	}
	string temp;
	temp += parent->value;
	command->data.push_back(eventReturnData(parent->id, parent->cords, parent->className, parent->health, temp, NULL, parent->isSelected(input_team), parent->team));
}


// select team [int:team] {flags}
void Unit::selectTeamCommand(Command_c* command, CommandPatterns* oParent) {
	Unit* parent = dynamic_cast<Unit*>(oParent);
	if (!parent) {
		return;
	}
	int input_team = 0;
	try {
		input_team = stoi(command->args[2].first);
	}
	catch (...) {
		return;
	}
	if (command->checkFlag("-cl")) {
//		cout << "clearing team " << input_team << " selection" << endl;
		parent->unselect(input_team);
	}
}

