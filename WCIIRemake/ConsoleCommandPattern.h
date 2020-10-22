#pragma once
#include "Command_c.h"
#include "Obj.h"

class CommandPatterns;

class ConsoleCommandPattern : public Command_c {
public:
	string name;
	string usingHelpMessage;
	void (*callback_func)(Command_c*, CommandPatterns*);
//	Obj* parent;
public:
	ConsoleCommandPattern(string command, string name, string usingHelpMessage, void (*callback_func)(Command_c*, CommandPatterns*)/*, Obj* parent*/);
	virtual ~ConsoleCommandPattern();
};

