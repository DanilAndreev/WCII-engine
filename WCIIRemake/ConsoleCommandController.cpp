#include "pch.h"
#include "ConsoleCommandController.h"

extern Console* defaultConsole;

ConsoleCommandController::ConsoleCommandController(Console* ioconsole, Controller* mainController) {
	if (ioconsole != NULL) {
		this->console = ioconsole;
	}
	else {
		this->console = defaultConsole;
	}
	this->CommandHandlerRunning = false;
	this->mainController = mainController;
}


ConsoleCommandController::~ConsoleCommandController() {
}

bool ConsoleCommandController::readCondition(char character) {
	//	if ((isalnum(character) || character == '-') && character != 0) {
	if ((character != ' ') && character != 0) {
		return true;
	}
	return false;
}

string ConsoleCommandController::commandType(char character) {
	if (character == '-') {
		return "flag";
	}
	if (isalpha(character)) {
		return "command";
	}
	if (isdigit(character)) {
		return "number";
	}
	return "unknown";
}

pair <string, string> ConsoleCommandController::nextToken(string command) {
	bool readBegin = true;
	pair <string, string> temp;
	while (!readCondition(command[ParserPosition])) {
		if (command[ParserPosition] == 0) {
			temp.first = "\0";
			temp.second = "end";
			return temp;
		}
		ParserPosition++;
	}


	while (readCondition(command[ParserPosition])) {
		temp.first += command[ParserPosition];
		if (readBegin) {
			temp.second = commandType(temp.first[0]); // add better classification for commands
		}
		readBegin = false;
		ParserPosition++;
	}
	return temp;
}


void ConsoleCommandController::initParser() {
	ParserPosition = 0;
}

Command_c ConsoleCommandController::parseCommand(string command)
{
	initParser();
	if (command.length() == 0) {
		return Command_c("empty");
	}
	pair <string, string> temp;
	Command_c command_c;
	temp = nextToken(command);
	for (int i = 0; temp.second != "end"; i++) {
		command_c.args.push_back(temp);
		temp = nextToken(command);
	}
	return command_c;
}

Command_c ConsoleCommandController::getCommand() {
	string command;
	command = console->getLine();
	return parseCommand(command);
}

void ConsoleCommandController::throwCommand(Command_c command) {
	mainController->addEventToQueue(command);
}

void ConsoleCommandController::CommandHandler() {
	cout << "CommandHandler" << endl;
	this->CommandHandlerRunning = true;
	while (CommandHandlerRunning) {
		Command_c command = getCommand();
		if (command.args[0].first != "empty") {
			throwCommand(command);
		}
	}
	this->CommandHandlerRunning = false;
}

void ConsoleCommandController::threadFunction() {
	CommandHandler();
}
