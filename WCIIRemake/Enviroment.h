#pragma once
#include "Unit.h"

class EnviromentPreset {
public:
	string name;
	string beautyName;
	char symbol;
	int width;
	int heigth;
	int type;
	EnviromentPreset(string name, string beautyName, char symbol, int width, int heigth, int type);
	EnviromentPreset() : EnviromentPreset("default", "Default", 'd', 1, 1, 1) {}
	~EnviromentPreset();
};


class Enviroment : public Unit {
public:
	Enviroment(EnviromentPreset preset, Field* field);
	~Enviroment();
protected:
	virtual void fillEventPatterns();
public: //ENVIROMENT EVENTS
	static void writeToCommand(Command_c* command, Eventable* oParent);
};

// write data to [string:filename]