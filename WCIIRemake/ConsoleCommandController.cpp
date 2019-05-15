#include "pch.h"
#include "ConsoleCommandController.h"


extern Console* defaultConsole;
extern Controller* gameController;
extern ThreadDescriptor* gameThreads;

ConsoleCommandController::ConsoleCommandController(Console* ioconsole, Controller* mainController) {
	this->fillCommandPatterns();

	if (ioconsole != NULL) {
		this->console = ioconsole;
	}
	else {
		this->console = defaultConsole;
	}

	if (mainController != NULL) {
		this->mainController = mainController;
	}
	else {
		this-> mainController = gameController;
	}

	this->CommandHandlerRunning = false;

	ConsoleCommandControllerTHREAD* ConComConTHRD = new ConsoleCommandControllerTHREAD(this);

	if (ConComConTHRD) {
		this->ConComConTHRDescriptor  = ConComConTHRD->getDescriptor();
	}
	else {
		defaultConsole->error("Error allocating memory");
	}
	this->isPaused = false;
	this->isRunning = true;
	ConComConTHRD->startThread();

	ConsoleCommandHandlerTHREAD* ConsoleComandHandleThread = new ConsoleCommandHandlerTHREAD(this);
	if (ConsoleComandHandleThread) {
		this->CommandHandlerTHRDDescriptor = ConsoleComandHandleThread->getDescriptor();
		ConsoleComandHandleThread->startThread();
	}
	else {
		defaultConsole->error("Error allocating memory");
	}
}


ConsoleCommandController::~ConsoleCommandController() {
	this->isRunning = false;
	gameThreads->stopThread(this->ConComConTHRDescriptor);
	gameThreads->stopThread(this->CommandHandlerTHRDDescriptor);
}

bool ConsoleCommandController::setController(Controller* mainController) {
	return this->mainController = mainController;
}

bool ConsoleCommandController::setConsole(Console* ioconsole) {
	return this->console = ioconsole;
}

bool ConsoleCommandController::readCondition(char character) {
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
			temp.second = commandType(temp.first[0]);
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

void ConsoleCommandController::pause() {
	this->isPaused = true;
}

void ConsoleCommandController::unpause() {
	this->isPaused = false;
}

Command_c ConsoleCommandController::getCommand() {
	string command;
	command = console->getLine();
	return parseCommand(command);
}

bool ConsoleCommandController::operateConsoleCommand(Command_c command) {
	if (selectSymbPattern ^= command) {
		this->mainController->addEventToQueue(Command_c(string("select ")+command.args[1].first));
		return true;
	}


	return false;
}

void ConsoleCommandController::throwCommand(Command_c* command) { //--------------------------------------------------------------MODIFIED
//	mainController->addEventToQueue(*command);
	this->addCommandToQueue(*command);
}

void ConsoleCommandController::operateEvent(Command_c* command) {
	if (*command == "exitgame") {
		exitGame(command);
	}
	if (*command == "stop") {
		stopEvent(command);
	}
	if (*command == "pause") {
		pauseEvent(command);
	}
	if (*command == "unpause") {
		unpauseEvent(command);
	}
}

//CONSOLE COMMAND CONTROLLER COMMANDS(EVENTS)

bool ConsoleCommandController::exitGame(Command_c* command) {
	if (command->args.size() == 1) {
		return gameThreads->stopThread(ConComConTHRDescriptor);
	}
	return false;
}


bool ConsoleCommandController::stopEvent(Command_c* command) {
	if (command->args.size() >= 2) {
		if (command->args[1].first == "threads" && command->args[1].second == "command") {
			if (!command->checkFlag("-ccc")) {
				//gameThreads->stopThread(ConComConTHRDescriptor, "ConsoleCommandControllerTHREAD");
				HANDLE temp_handle;
				if ((temp_handle = gameThreads->stopThread(ConComConTHRDescriptor)) != NULL) {
					command->data.push_back(temp_handle);
				}

				fprintf(stdin, "\n");
//				cout << "stpping Console Command Controller thread by event" << endl;
			}
			return true;
		}
	}
	return false;
}

bool ConsoleCommandController::pauseEvent(Command_c* command) {
	if (command->args.size() >= 1) {
		if (command->checkFlag("-command_input")) {
			this->pause();
		}
		return true;
	}
	return false;
}

bool ConsoleCommandController::unpauseEvent(Command_c* command) {
	if (command->args.size() >= 1) {
		if (command->checkFlag("-command_input")) {
			this->unpause();
		}
		return true;
	}
	return false;
}


Command_c ConsoleCommandController::getCommandFromQueue() {
	Command_c command;
	command = commandQueue.front();
	commandQueue.pop();
	return command;
}

bool ConsoleCommandController::addCommandToQueue(Command_c command) {
	this->commandQueue.push(command);
	return true;
}

bool ConsoleCommandController::commandQueueIsEmpty() {
	return this->commandQueue.empty();
}

void ConsoleCommandController::fillCommandPatterns() {
	this->commandPatterns.push_back(selectCordsPattern);
	this->commandPatterns.push_back(selectSymbPattern);
	this->commandPatterns.push_back(selectIdPattern);
	this->commandPatterns.push_back(moveToPattern);
}

void ConsoleCommandController::handleCommand(bool & flag) {
	if (flag) {
		if (!commandQueueIsEmpty()) {
			Command_c temp = getCommandFromQueue();
			operateConsoleCommand(temp);
		}
		else {
			Sleep(10);
		}
	}
}