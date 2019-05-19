#include "pch.h"
#include "Field.h"

extern Console* defaultConsole;
extern GameMaster* gameMaster;


Field::Field(int width, int heigth){
	this->layer = 100;
	fillEventPatterns();
	setDescription("Field");
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
			target->settingUp();
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

void Field::render(int layer) {

	for (int i = 0; i < members->count(); i++) {
	((Screenable*)(members->get(i)))->render(layer);
	}
}

void Field::catchEvent(Command_c* command, bool showHelp) {
	for (int i = 0; i < members->count(); i++) {
		members->get(i)->operateEvent(command, showHelp);
	}
	operateEvent(command, showHelp);
}

void Field::fillEventPatterns() {
	const EventPattern writeToPattern(
		"write data to input_command",
		"writeToPattern",
		"write data to [string:savename]",
		Field::writeDataToCommand);
	const EventPattern spawnUnitArgsPattern(
		"spawn unit cords input_number input_number team input_number health input_number attackLength input_number type input_number symbol input_command cooldown input_number speed input_number power input_number",
		"spawnUnitArgsPattern",
		"spawn unit cords [int:x] [int:y] team [int:team] health [int:health] attackLength [int:length] type [int:type] symbol [char:symbol] cooldown [int:cooldown] speed [int:speed] power [int:power]",
		Field::spawnUnitArgsCommand);
	const EventPattern spawnUnitPresetPattern(
		"spawn team input_number unit input_command cords input_number input_number",
		"spawnUnitPresetPattern",
		"spawn team [int:team] unit [string:preset name] cords [int:x] [int:y]",
		Field::spawnUnitPresetCommand);
	const EventPattern spawnBuildingArgsPattern(
		"spawn building cords input_number input_number team input_number health input_number type input_number symbol input_command",
		"spawnBuildingArgsPattern",
		"spawn building cords [int:x] [int:y] team [int:team] health [int:health] type [int:type] symbol [char:symbol]",
		Field::spawnBuildingArgsCommand);
	this->eventPatterns.push_back(writeToPattern);
	this->eventPatterns.push_back(spawnUnitArgsPattern);
	this->eventPatterns.push_back(spawnUnitPresetPattern);
	this->eventPatterns.push_back(spawnBuildingArgsPattern);
}

// FIELD EVENTS

// write data to [string:savename]
void Field::writeDataToCommand(Command_c* command, Eventable* oParent) {
	Field* parent = dynamic_cast<Field*>(oParent);
	if (!parent) {
		return;
	}
	string input_filename = command->args[3].first;
	FileWriter writer(input_filename, ios::app);
	writer << " field {";
	writer << " width:" << parent->width << ";";
	writer << " heigth:" << parent->heigth << ";";
	writer << "}" << endl;
}

// spawn unit cords [int:x] [int:y] team [int:team] health [int:health] attackLength [int:length] type [int:type] symbol [char:symbol] cooldown [int:cooldown] speed [int:speed] power [int:power]
void Field::spawnUnitArgsCommand(Command_c* command, Eventable* oParent) {
	Field* parent = dynamic_cast<Field*>(oParent);
	if (!parent) {
		return;
	}
//	ID input_id = 0;
	int input_cord_x = 0;
	int input_cord_y = 0;
	int input_team = 0;
	int input_health = 0;
	int input_attackLength = 0;
	int input_type = 0;
	int input_cooldown = 0;
	int input_speed = 0;
	int input_power = 0;
	try {
		input_cord_x = stoi(command->args[3].first);
		input_cord_y = stoi(command->args[4].first);
		input_team = stoi(command->args[6].first);
		input_health = stoi(command->args[8].first);
		input_attackLength = stoi(command->args[10].first);
		input_type = stoi(command->args[12].first);
		input_cooldown = stoi(command->args[16].first);
		input_speed = stoi(command->args[18].first);
		input_power = stoi(command->args[20].first);
		//input_id = stoull(command->args[4].first);
	}
	catch (...) {
		return;
	}
	cordScr input_cords(input_cord_x, input_cord_y);
	string input_string_symbol = command->args[14].first;
	char input_symbol = input_string_symbol[0];

	LiveUnit* unit = new LiveUnit(input_symbol, input_type, parent, input_health, input_team, input_attackLength, input_cooldown, input_speed, input_power);
	parent->setCell(input_cords, (Unit*)unit);
}

// spawn team [int:team] unit [string:preset name] cords [int:x] [int:y]
void Field::spawnUnitPresetCommand(Command_c* command, Eventable* oParent) {
	Field* parent = dynamic_cast<Field*>(oParent);
	if (!parent) {
		return;
	}
	//ID input_id = 0;
	int input_team = 0;
	int input_cord_x = 0;
	int input_cord_y = 0;
	try {
		input_team = stoi(command->args[2].first);
		input_cord_x = stoi(command->args[6].first);
		input_cord_y = stoi(command->args[7].first);
		//input_id = stoull(command->args[4].first);
	}
	catch (...) {
		return;
	}
	cordScr input_cords(input_cord_x, input_cord_y);
	string input_preset_name = command->args[4].first;
	LiveUnitPreset* preset = gameMaster->getUnitPreset(input_preset_name);
	if (preset) {
		LiveUnit* unit = new LiveUnit(*preset, parent, input_team);
		parent->setCell(input_cords, (Unit*)unit);
	}
}

// spawn building cords [int:x] [int:y] team [int:team] health [int:health] type [int:type] symbol [char:symbol]
void Field::spawnBuildingArgsCommand(Command_c* command, Eventable* oParent) {
	Field* parent = dynamic_cast<Field*>(oParent);
	if (!parent) {
		return;
	}
	//	ID input_id = 0;
	int input_cord_x = 0;
	int input_cord_y = 0;
	int input_team = 0;
	int input_health = 0;
	int input_type = 0;
	try {
		input_cord_x = stoi(command->args[3].first);
		input_cord_y = stoi(command->args[4].first);
		input_team = stoi(command->args[6].first);
		input_health = stoi(command->args[8].first);
		input_type = stoi(command->args[10].first);
		//input_id = stoull(command->args[4].first);
	}
	catch (...) {
		return;
	}
	cordScr input_cords(input_cord_x, input_cord_y);
	string input_string_symbol = command->args[12].first;
	char input_symbol = input_string_symbol[0];

	Building* unit = new Building(input_symbol, input_type, parent, input_health, input_team);
	parent->setCell(input_cords, (Unit*)unit);
}
