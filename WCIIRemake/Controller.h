#pragma once
#include "pch.h"
#include "Obj.h"
#include "Threadable.h"
//#include "Command_c.h"


class Controller : public Obj, public Threadable {
private:
	Console *console;
	Field* field;
	MScreen* screen;
	DynArr* members;
	int ParserPosition;
	bool EventHandlerRunning;
public:
	Controller(Field* ifield, MScreen* screen, Console* ioconsole);
	~Controller();
public: // change to private!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	bool readCondition(char character);
	string commandType(char character);
	pair <string, string> nextToken(string command);
	void initParser();
	Command_c getCommand();
	Command_c parseCommand(string command);
	void throwCommand(Command_c command);
	void EventHandler();
	virtual void operateEvent(Command_c command);
private:
	virtual void threadFunction();

//CONTROLLER COMMANDS(EVENTS)
private:
	bool exitGame(Command_c command);

};

