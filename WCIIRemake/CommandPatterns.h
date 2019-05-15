#pragma once
class CommandPatterns {
public:
	vector <ConsoleCommandPattern> commandPatterns;
public:
	CommandPatterns();
	virtual ~CommandPatterns();
	virtual void fillCommandPatterns() = 0;
protected:
	ConsoleCommandPattern searchPatternByName(string name);
	ConsoleCommandPattern searchPatternByCommandName(string commandName); // the name of command
};

