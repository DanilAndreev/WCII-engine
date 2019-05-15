//TODO : ADD THIS TO CONTROLLER EVENT MEMBERS
#pragma once
#include "pch.h"
#include "Command_c.h"
#include "ConsoleCommandPattern.h"
#include "Obj.h"
#include "ConsoleCommandControllerTHREAD.h"
#include "ConsoleCommandHandlerTHREAD.h"

const ConsoleCommandPattern selectCordsPattern("select input_number input_number", 
												"selectCordsPattern", 
												"select [int:x] [int:y]",
												selectCordsCommnad);
const ConsoleCommandPattern selectSymbPattern("select input_command",
												"selectSymbPattern", 
												"select [cahr:symbol]");
const ConsoleCommandPattern selectIdPattern("select input_number",
												"selectIdPattern",
												"select [int:id]");
const ConsoleCommandPattern moveToPattern("move to input_number input_number",
												"moveToPattern", 
												"move to [int:x] [int:y]");

class ConsoleCommandController : public Obj{
protected:
	Controller* mainController;
	int ParserPosition;
	bool CommandHandlerRunning;
	ThreadId ConComConTHRDescriptor;
	ThreadId CommandHandlerTHRDDescriptor;
	queue <Command_c> commandQueue;
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
	bool operateConsoleCommand(Command_c command);
	void throwCommand(Command_c* command);
	void operateEvent(Command_c* command);

	void handleCommand(bool & flag);
protected:
	Command_c getCommandFromQueue();
	bool addCommandToQueue(Command_c command);
	bool commandQueueIsEmpty();
	virtual void fillCommandPatterns();
public:
//CONSOLE COMMAND CONTROLLER COMMANDS Functions
	void selectCordsCommnad(Command_c command);
	void selectSymbCommand(Command_c command);
	void selectIdCommnad(Command_c command);
	void moveToCommand(Command_c command);

//CONSOLE COMMAND CONTROLLER EVENTS
protected:
	bool exitGame(Command_c* command);
	bool stopEvent(Command_c* command);
	bool pauseEvent(Command_c* command);
	bool unpauseEvent(Command_c* command);
};

