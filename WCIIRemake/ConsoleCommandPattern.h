#pragma once
#include "Command_c.h"
#include "Obj.h"

class ConsoleCommandPattern : public Command_c {
public:
	string name;
	string usingHelpMessage;
	void (*callback_func)(Command_c*, Obj*);
//	Obj* parent;
public:
	ConsoleCommandPattern(string command, string name, string usingHelpMessage, void (*callback_func)(Command_c*, Obj*)/*, Obj* parent*/);
	virtual ~ConsoleCommandPattern();
};

