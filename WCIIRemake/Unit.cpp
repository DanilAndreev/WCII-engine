#include "pch.h"
#include "Unit.h"

extern Controller* gameController;
extern ThreadDescriptor* gameThreads;
extern Console* defaultConsole;

Unit::Unit(char value, int type, Field* field, int health, int team) {
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

void Unit::fillCommandPatterns() {
	const ConsoleCommandPattern selectIdPattern(
		"select team input_number id input_number",
		"selectIdPattern",
		"select team [int:team] id [int::id]",
		Unit::selectIdCommand);
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
		Unit::echoIdCommand);

	this->commandPatterns.push_back(selectIdPattern);
	this->commandPatterns.push_back(dammageIdPattern);
	this->commandPatterns.push_back(getInfoIdPattern);
	this->commandPatterns.push_back(echoIdPattern);
}


bool Unit::operateConsoleCommand(Command_c* command, bool showHelp) {
	for (unsigned int i = 0; i < this->commandPatterns.size(); i++) {
		if (commandPatterns[i] ^= *command) {
			commandPatterns[i].callback_func(command, this);
			return true;
		}
	}

	if (showHelp) {
		defaultConsole->error("Invalid command");
		for (unsigned int i = 0; i < this->commandPatterns.size(); i++) {
			if (commandPatterns[i] == *command) {
				defaultConsole->warning(string("Usage: ") + commandPatterns[i].usingHelpMessage);
			}
		}
	}
	return false;
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


//select team [int:team] id [int:id]
void Unit::selectIdCommand(Command_c * command, Obj * oParent) {
	if (stoi(command->args[4].first) == this->id) {
		this->selected = true;
	}
}

//damage id [int:id] power [int:power]
void Unit::damageIdCommand(Command_c * command, Obj * oParent) {
	ID input_id = 0;
	int input_damage = 0;
	try {
		input_id = stoull(command->args[2].first);
		input_damage = stoi(command->args[4].first);
	}
	catch (...) {
		return;
	}
	if (input_id == this->id) {
		this->getDamage(input_damage);
	}
}

// get info id [int::id]
void Unit::getInfoIdCommand(Command_c * command, Obj * oParent) {
	ID input_id = 0;
	try {
		input_id = stoull(command->args[2].first);
	}
	catch (...) {
		return;
	}
	if (this->id == input_id) {
		string temp;
		temp += this->value;
		command->data.push_back(eventReturnData(this->id, this->cords, this->className, this->health, temp, NULL));
	}
}



void Unit::echoIdCommand(Command_c * command, Obj * oParent) {
}
