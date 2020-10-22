#pragma once
#include "Obj.h"
#include "EventPattern.h"

class Eventable {
public:
	vector <EventPattern> eventPatterns;
public:
	Eventable();
	virtual ~Eventable();
	virtual void fillEventPatterns();
	bool operateEvent(Command_c* command, bool showHelp);
	virtual void catchEvent(Command_c* command, bool showHelp);
protected:
	EventPattern searchPatternByName(string name);
	EventPattern searchPatternByCommandName(string commandName); // the name of command
};

