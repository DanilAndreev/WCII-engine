#pragma once
#include "Command_c.h"

class ConsoleCommandPattern : public Command_c {
public:
	string name;
	string usingHelpMessage;
	void (*callback_func)(Command_c);
public:
	ConsoleCommandPattern(string command, string name, string usingHelpMessage, void (*callback_func)(Command_c));
	virtual ~ConsoleCommandPattern();
};

