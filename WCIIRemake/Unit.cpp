#include "pch.h"
#include "Unit.h"

extern Controller* gameController;
extern ThreadDescriptor* gameThreads;
extern Console* defaultConsole;

Unit::Unit(char value, int type, Field* field, int health, int team) {
	this->fillEventPatterns();
	this->team = team;
	this->value = value;
	this->field = field;
	this->type = type;
	this->threadFlag = false;
	this->health = health;
	this->layer = this->type + 100;
	this->width = 1;
	this->heigth = 1;
	this->attackLength = 0;
//	cout << "Constructor: created unit " << this->value << " type " << this->type << endl;
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





void Unit::render(int layer, int team) {
	if (parentScreen != NULL /*&& this->layer == layer*/) { 
		cordScr shift;
		if (field) {
			shift = this->field->getCords();
		}
		CScreenPixel pixel(this->value, COLOR_WHITE);

		if (this->isSelected(team)) {
			pixel.color = COLOR_YELLOW;
		}
		parentScreen->putToBuff(this->cords + shift, pixel);
	}
}

void Unit::render(int team) {
	this->render(0, team);
}

void Unit::catchEvent(Command_c* command, bool showHelp) {
	this->operateEvent(command, showHelp);
}

bool Unit::getDamage(int damage) {
	if (health > 0) {
		this->health -= damage;
		Beep(500, 70);
		if (this->health < 0) {
			health = 0;
			this->value = '#';
			this->type = 100;
			stopAllThreads();
		}
		return true;
	}
	else {
		this->value = '#';
		this->type = 100;
		stopAllThreads();
	}
	return false;

}

void Unit::stopAllThreads() {
}

void Unit::fillEventPatterns() {
	const EventPattern selectIdPattern(
		"select team input_number id input_number",
		"selectIdPattern",
		"select team [int:team] id [int::id]",
		Unit::selectIdCommand);
	const EventPattern unselectIdPattern(
		"unselect team input_number id input_number",
		"unselectIdPattern",
		"unselect team [int:team] id [int::id]",
		Unit::unselectIdCommand);
	const EventPattern selectTeamPattern(
		"select team input_number",
		"selectTeamPattern",
		"select team [int:team] {flags}",
		Unit::selectTeamCommand);
	const EventPattern dammageIdPattern(
		"damage id input_number power input_number",
		"damageIdPattern",
		"damage id [int:id] power [int::power]",
		Unit::damageIdCommand);
	const EventPattern getInfoIdPattern(
		"get info id input_number",
		"getInfoIdPattern",
		"get info id [int::id]",
		Unit::getInfoIdCommand);
	const EventPattern echoIdPattern(
		"echo id input_number input_command",
		"echoIdPattern",
		"echo id [int:id] [quotes string:message]",
		Unit::echoIdCommand);
	const EventPattern getInfoUnitsPattern(
		"get info units",
		"getInfoUnitsPattern",
		"get info units",
		Unit::getInfoUnitsCommand);
	const EventPattern getInfoTeamUnitsPattern(
		"get team input_number info units",
		"getInfoTeamUnitsPattern",
		"get team [int:team] info units",
		Unit::getInfoTeamUnitsCommand);
	const EventPattern renderLayerPattern(
		"render layer",
		"renderLayerPattern",
		"render layer {flags}",
		Unit::renderLayerCommand);

	this->eventPatterns.push_back(selectIdPattern);
	this->eventPatterns.push_back(unselectIdPattern);
	this->eventPatterns.push_back(selectTeamPattern);
	this->eventPatterns.push_back(dammageIdPattern);
	this->eventPatterns.push_back(getInfoIdPattern);
	this->eventPatterns.push_back(echoIdPattern);
	this->eventPatterns.push_back(getInfoUnitsPattern);
	this->eventPatterns.push_back(getInfoTeamUnitsPattern);
	this->eventPatterns.push_back(renderLayerPattern);
}

//UNIT EVENTS

// select team [int:team] id [int:id]
void Unit::selectIdCommand(Command_c * command, Eventable* oParent) {
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
		//cout << "selected unit: " << parent->value << " , ID : " << parent->id << endl;
	}
}

// unselect team [int:team] id [int::id]
void Unit::unselectIdCommand(Command_c* command, Eventable* oParent) {
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
void Unit::damageIdCommand(Command_c * command, Eventable* oParent) {
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
void Unit::getInfoIdCommand(Command_c * command, Eventable* oParent) {
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
		command->data.push_back(new eventReturnDataUnitInfo(parent->id, parent->cords, parent->className, parent->health, temp, NULL, parent->team));
	}
}


// echo id [int:id] [quotes string:message]
void Unit::echoIdCommand(Command_c * command, Eventable* oParent) {
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
void Unit::getInfoUnitsCommand(Command_c* command, Eventable* oParent) {
	Unit* parent = dynamic_cast<Unit*>(oParent);
	if (!parent) {
		return;
	}
	string temp;
	temp += parent->value;
	command->data.push_back(new eventReturnDataUnitInfo(parent->id, parent->cords, parent->className, parent->health, temp, NULL, parent->team));
}

// get team [int:team] info units
void Unit::getInfoTeamUnitsCommand(Command_c* command, Eventable* oParent) {
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
	command->data.push_back(new eventReturnDataUnitInfo(parent->id, parent->cords, parent->className, parent->health, temp, NULL, parent->isSelected(input_team), parent->team));
}


// select team [int:team] {flags}
void Unit::selectTeamCommand(Command_c* command, Eventable* oParent) {
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

void Unit::renderLayerCommand(Command_c* command, Eventable* oParent) {
	Unit *parent = dynamic_cast<Unit*>(oParent);
	if (!parent) {
		return;
	}
	if (command->checkFlag("-query")) {
		eventReturnDataUnitInfo* temp =  new eventReturnDataUnitInfo();
		temp->layer = parent->layer;
		command->data.push_back(temp);
	}
}

