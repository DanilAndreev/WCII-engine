#pragma once
#include "pch.h"
#include "Command_c.h"
#include "Obj.h"
//#include "Threadable.h"
#include "ConsoleCommandControllerTHREAD.h"

class ConsoleCommandController : public Obj{
private:
//	Console *console;
	Controller* mainController;
	int ParserPosition;
	bool CommandHandlerRunning;
	ThreadId ConComConTHRDescriptor;
public:
	Console *console;
public:
	ConsoleCommandController(Console* ioconsole, Controller* mainController);
	~ConsoleCommandController();
	Command_c parseCommand(string command); // Parse the command
public:
	bool readCondition(char character);
	string commandType(char character);
	pair <string, string> nextToken(string command);
	void initParser();
	Command_c getCommand();
	void throwCommand(Command_c command);
//	void CommandHandler();
//	virtual void threadFunction();
};

