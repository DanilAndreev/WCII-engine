#pragma once
#include "Command_c.h"
#include "Obj.h"

class Eventable;

class EventPattern : public Command_c {
public:
	string name;
	string usingHelpMessage;
	void (*callback_func)(Command_c*, Eventable*);
public:
	EventPattern(string command, string name, string usingHelpMessage, void (*callback_func)(Command_c*, Eventable*));
	virtual ~EventPattern();
};

