#pragma once
#include "ConsoleCommandPattern.h"
#include "Obj.h"

class CommandPatterns{
public:
	vector <ConsoleCommandPattern> commandPatterns;
public:
	CommandPatterns();
	virtual ~CommandPatterns();
	virtual void fillCommandPatterns() = 0;
	bool operateConsoleCommand(Command_c* command, bool showHelp);
protected:
	ConsoleCommandPattern searchPatternByName(string name);
	ConsoleCommandPattern searchPatternByCommandName(string commandName); // the name of command
};

