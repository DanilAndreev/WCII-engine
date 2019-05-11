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
	bool isRunning;
public:
	bool isPaused;
	Console *console;
public:
	ConsoleCommandController(Console* ioconsole, Controller* mainController);
	~ConsoleCommandController();
	bool setController(Controller* mainController);
	bool setConsole(Console* ioconsole);
	Command_c parseCommand(string command); // Parse the command
	void pause();
	void unpause();
public:
	bool readCondition(char character);
	string commandType(char character);
	pair <string, string> nextToken(string command);
	void initParser();
	Command_c getCommand();
	void throwCommand(Command_c* command);
	void operateEvent(Command_c* command);
//CONSOLE COMMAND CONTROLLER COMMANDS(EVENTS)
protected:
	bool exitGame(Command_c* command);
	bool stopEvent(Command_c* command);
	bool pauseEvent(Command_c* command);
	bool unpauseEvent(Command_c* command);
};

