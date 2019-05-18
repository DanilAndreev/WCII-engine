//TODO : ADD THIS TO CONTROLLER EVENT MEMBERS
#pragma once
#include "pch.h"
#include "Command_c.h"
#include "ConsoleCommandPattern.h"
#include "CommandPatterns.h"
#include "Obj.h"
#include "ConsoleCommandControllerTHREAD.h"
#include "ConsoleCommandHandlerTHREAD.h"


class ConsoleCommandController : public Obj, public CommandPatterns{
protected:
	Controller* mainController;
	int ParserPosition;
	bool CommandHandlerRunning;
	ThreadId ConComConTHRDescriptor;
	ThreadId CommandHandlerTHRDDescriptor;
	queue <Command_c> commandQueue;
	bool isRunning;
	int team;
public:
	bool isPaused;
	Console *console;
public:
	ConsoleCommandController(Console* ioconsole, Controller* mainController, int team);
	~ConsoleCommandController();
	bool setController(Controller* mainController);
	bool setConsole(Console* ioconsole);
	Command_c parseCommand(string command); // Parse the command
	void pause();
	void unpause();
	void setTeam(int newteam);
public:
	bool readCondition(char character);
	string commandType(char character);
	pair <string, string> nextToken(string command);
	void initParser();
	Command_c getCommand();
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
	static void selectCordsCommand(Command_c* command, CommandPatterns* oParent);
	static void selectSymbCommand(Command_c* command, CommandPatterns* oParent);
	static void selectIdCommand(Command_c* command, CommandPatterns* oParent);
	static void moveToCommand(Command_c* command, CommandPatterns* oParent);
	static void attackCordsCommand(Command_c* command, CommandPatterns* oParent);
	static void exitGameCommand(Command_c* command, CommandPatterns* oParent);
	static void saveGameCommand(Command_c* command, CommandPatterns* oParent);
	static void loadGameCommand(Command_c* command, CommandPatterns* oParent);
	static void spawnUnitPresetCommand(Command_c* command, CommandPatterns* oParent);
	
	//CONSOLE COMMAND CONTROLLER EVENTS
protected:
	bool exitGame(Command_c* command);
	bool stopEvent(Command_c* command);
	bool pauseEvent(Command_c* command);
	bool unpauseEvent(Command_c* command);
};

