#pragma once
#include "pch.h"
//#include "Command_c.h"


class Controller {
private:
	Console *console;
	Field* field;
	DynArr* members;
	int ParserPosition;
public:
	Controller(Field* ifield,/* MScreen* screen,*/ Console* ioconsole);
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
};

