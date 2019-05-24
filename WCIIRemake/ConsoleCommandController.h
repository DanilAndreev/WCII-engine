//TODO : ADD THIS TO CONTROLLER EVENT MEMBERS
#pragma once
#include "pch.h"
#include "Command_c.h"
#include "ConsoleCommandPattern.h"
#include "CommandPatterns.h"
#include "Obj.h"
#include "ConsoleCommandControllerTHREAD.h"
#include "ConsoleCommandHandlerTHREAD.h"
#include <conio.h>

class ConsoleCommandController : public Obj, public CommandPatterns{
protected:
	Controller* mainController;
	int ParserPosition;
	bool CommandHandlerRunning;
	ThreadId ConComConTHRDescriptor;
	ThreadId CommandHandlerTHRDDescriptor;
	queue <Command_c> commandQueue;
	bool isRunning;
public:
	int team;
	bool isPaused;
	Console *console;
	bool commandInput;
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
	KeyID getKey();
	void switchUI();
	void throwCommand(Command_c* command);
	void handleCommand(bool & flag);
	virtual void catchEvent(Command_c* command, bool showHelp);
protected:
	Command_c getCommandFromQueue();
	bool addCommandToQueue(Command_c command);
	bool commandQueueIsEmpty();
	virtual void fillCommandPatterns();
public:
	//CONSOLE COMMAND CONTROLLER COMMANDS Functions
	static void selectCordsCommand(Command_c* command, CommandPatterns* oParent);
	static void selectCordsAreaCommand(Command_c* command, CommandPatterns* oParent);
	static void selectSymbCommand(Command_c* command, CommandPatterns* oParent);
	static void selectIdCommand(Command_c* command, CommandPatterns* oParent);
	static void moveToCommand(Command_c* command, CommandPatterns* oParent);
	static void attackCordsCommand(Command_c* command, CommandPatterns* oParent);
	static void exitGameCommand(Command_c* command, CommandPatterns* oParent);
	static void saveGameCommand(Command_c* command, CommandPatterns* oParent);
	static void loadGameCommand(Command_c* command, CommandPatterns* oParent);
	static void spawnUnitPresetCommand(Command_c* command, CommandPatterns* oParent);
	static void stopUnitsCommand(Command_c* command, CommandPatterns* oParent);
	static void changTeamCommand(Command_c* command, CommandPatterns* oParent);
	static void switchUICommand(Command_c* command, CommandPatterns* oParent);
	static void clearConsoleCommand(Command_c* command, CommandPatterns* oParent);
	static void refreshInputsCommand(Command_c* command, CommandPatterns* oParent);
	static void newFieldCommand(Command_c* command, CommandPatterns* oParent);
	static void setupSpawnerCommand(Command_c* command, CommandPatterns* oParent);

	static void renderScreenCommand(Command_c* command, CommandPatterns* oParent);
protected:
	virtual void fillEventPatterns();
public:// CONSOLE COMMAND CONTROLLER EVENTS
	static void exitGameCommand(Command_c* command, Eventable* oParent);
	static void stopThreadsCommand(Command_c* command, Eventable* oParent);
	static void pauseCommand(Command_c* command, Eventable* oParent);
	static void unpauseCommand(Command_c* command, Eventable* oParent);
	static void keyPressIdCommand(Command_c* command, Eventable* oParent);
	
};

//EVENTS:
// exitgame
// stop threads {flags}
// pause {flags}
// unpause {flags}

//CONSOLE COMMANDS:
/*
spawn team [int:team] unit [string:unit name] [int:x] [int:y]
load game [string:savename]
save game [string:savename]
exit game
attack [int:x] [int:y]
move to [int:x] [int:y]
select [int:id]
select [char:symbol]
select [int:x] [int:y]
change team [int:team]
setup spawner [string:preset type] [string:preset name] team [int:team]
new field [string:name] [int:width] [int:heigth]
refresh inputs
switch ui

render screen {flags}
*/