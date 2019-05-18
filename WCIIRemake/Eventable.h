#pragma once
#include "Obj.h"
#include "EventPattern.h"

class Eventable {
public:
	vector <EventPattern> eventPatterns;
public:
	Eventable();
	virtual ~Eventable();
	virtual void fillEventPatterns() = 0;
	bool operateEvents(Command_c* command, bool showHelp);
protected:
	EventPattern searchPatternByName(string name);
	EventPattern searchPatternByCommandName(string commandName); // the name of command
};

