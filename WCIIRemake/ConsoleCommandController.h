//TODO : ADD THIS TO CONTROLLER EVENT MEMBERS
#pragma once
#include "pch.h"
#include "Command_c.h"
#include "Obj.h"
#include "ConsoleCommandControllerTHREAD.h"

class ConsoleCommandController : public Obj{
private:
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
	void operateEvent(Command_c command);
//CONSOLE COMMAND CONTROLLER COMMANDS(EVENTS)
protected:
	bool exitGame(Command_c command);
};

