#include "pch.h"
#include "Enviroment.h"

EnviromentPreset::EnviromentPreset(string name, string beautyName, char symbol, int width, int heigth, int type) {
	this->name = name;
	this->beautyName = beautyName;
	this->symbol = symbol;
	this->width = width;
	this->heigth = heigth;
	this->type = type;
}

EnviromentPreset::~EnviromentPreset() {
}




Enviroment::Enviroment(EnviromentPreset preset, Field* field) : Unit(preset.symbol, preset.type, field, 100, 0) {
	this->fillEventPatterns();
}


Enviroment::~Enviroment() {
}

void Enviroment::fillEventPatterns() {
	const EventPattern writeToPattern(
		"write data to input_command",
		"writeToPattern",
		"write data to [string:filename]",
		Enviroment::writeToCommand);

	this->eventPatterns.push_back(writeToPattern);
}

void Enviroment::writeToCommand(Command_c* command, Eventable* oParent) {
	Enviroment* parent = dynamic_cast<Enviroment*>(oParent);
	if (!parent) {
		return;
	}
	string filename = command->args[3].first;
	FileWriter writer(filename, ios::app);
	writer << " enviroment {";
	writer << " x:" << parent->cords.x << ";";
	writer << " y:" << parent->cords.y << ";";
	writer << " symbol:\'" << parent->value << "\';";
	writer << " width:" << parent->width << ";";
	writer << " heigth:" << parent->heigth << ";";
	writer << " type:" << parent->type << ";";
	writer << "}" << endl;
}
