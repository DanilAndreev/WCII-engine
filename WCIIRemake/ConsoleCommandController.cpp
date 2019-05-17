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


void ConsoleCommandController::throwCommand(Command_c* command) { //--------------------------------------------------------------MODIFIED
//	mainController->addEventToQueue(*command);
	this->addCommandToQueue(*command);
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
	const ConsoleCommandPattern selectCordsPattern(
		"select input_number input_number",
		"selectCordsPattern",
		"select [int:x] [int:y]",
		ConsoleCommandController::selectCordsCommand);
	const ConsoleCommandPattern selectSymbPattern(
		"select input_command",
		"selectSymbPattern",
		"select [char:symbol]",
		ConsoleCommandController::selectSymbCommand);
	const ConsoleCommandPattern selectIdPattern(
		"select input_number",
		"selectIdPattern",
		"select [int:id]",
		ConsoleCommandController::selectIdCommand);
	const ConsoleCommandPattern moveToPattern(
		"move to input_number input_number",
		"moveToPattern",
		"move to [int:x] [int:y]",
		ConsoleCommandController::moveToCommand);
	const ConsoleCommandPattern attackCordsPattern(
		"attack input_number input_number",
		"attackPattern",
		"attack [int:x] [int:y]",
		ConsoleCommandController::attackCordsCommand);
	const ConsoleCommandPattern exitGamePattern(
		"exit game",
		"exitGamePattern",
		"exit game",
		ConsoleCommandController::exitGameCommand);
	const ConsoleCommandPattern saveGamePattern(
		"save game input_command",
		"saveGamePattern",
		"save game [string:savename]",
		ConsoleCommandController::saveGameCommand);
	const ConsoleCommandPattern loadGamePattern(
		"load game input_command",
		"loadGamePattern",
		"load game [string:savename]",
		ConsoleCommandController::loadGameCommand);
	const ConsoleCommandPattern spawnUnitPresetPattern(
		"spawn team input_number unit input_command input_number input_number",
		"loadGamePattern",
		"spawn team [int:team] unit [string:unit name] [int:x] [int:y]",
		ConsoleCommandController::spawnUnitPresetCommand);

	this->commandPatterns.push_back(selectCordsPattern);
	this->commandPatterns.push_back(selectSymbPattern);
	this->commandPatterns.push_back(selectIdPattern);
	this->commandPatterns.push_back(moveToPattern);
	this->commandPatterns.push_back(attackCordsPattern);
	this->commandPatterns.push_back(exitGamePattern);
	this->commandPatterns.push_back(saveGamePattern);
	this->commandPatterns.push_back(loadGamePattern);
	this->commandPatterns.push_back(spawnUnitPresetPattern);
}


void ConsoleCommandController::handleCommand(bool& flag) {
	if (flag) {
		if (!commandQueueIsEmpty()) {
			Command_c temp = getCommandFromQueue();
			operateConsoleCommand(&temp, true);
		}
		else {
			Sleep(10);
		}
	}
}

bool ConsoleCommandController::operateConsoleCommand(Command_c* command, bool showHelp) {
	for (unsigned int i = 0; i < this->commandPatterns.size(); i++) {
		if (commandPatterns[i] ^= *command) {
			commandPatterns[i].callback_func(command, this);
			return true;
		}
	}

	if (showHelp) {
		defaultConsole->error("Invalid command");
		for (unsigned int i = 0; i < this->commandPatterns.size(); i++) {
			if ( commandPatterns[i] == *command ) {
				defaultConsole->warning(string("Usage: ") + commandPatterns[i].usingHelpMessage);
			}
		}
	}
	return false;
}


//CONSOLE COMMAND CONTROLLER COMMANDS Fuctions
	
void ConsoleCommandController::selectCordsCommand(Command_c* command, Obj* oParent) {
	ConsoleCommandController* parent = dynamic_cast<ConsoleCommandController*>(oParent);
	if (!parent) {
		throw new exception("Bad input class type");
	}
	Command_c tempEvent(Command_c(string("select ") + command->args[1].first + " " + command->args[2].first));
	parent->mainController->addEventToQueue(tempEvent);
}

void ConsoleCommandController::selectSymbCommand(Command_c* command, Obj* oParent) {
	ConsoleCommandController* parent = dynamic_cast<ConsoleCommandController*>(oParent);
	if (!parent) {
		throw new exception("Bad input class type");
	}
	parent->mainController->addEventToQueue(Command_c(string("select ") + command->args[1].first));
}

void ConsoleCommandController::selectIdCommand(Command_c* command, Obj* oParent) {
	ConsoleCommandController* parent = dynamic_cast<ConsoleCommandController*>(oParent);
	if (!parent) {
		throw new exception("Bad input class type");
	}
	parent->mainController->addEventToQueue(Command_c(string("select ") + command->args[1].first));
}

void ConsoleCommandController::moveToCommand(Command_c* command, Obj* oParent) {
	ConsoleCommandController* parent = dynamic_cast<ConsoleCommandController*>(oParent);
	if (!parent) {
		throw new exception("Bad input class type");
	}
	Command_c tempEvent(string("move to ") + command->args[2].first + " " + command->args[3].first);
	parent->mainController->addEventToQueue(tempEvent);
}

void ConsoleCommandController::attackCordsCommand(Command_c* command, Obj* oParent) {
	ConsoleCommandController* parent = dynamic_cast<ConsoleCommandController*>(oParent);
	if (!parent) {
		throw new exception("Bad input class type");
	}
	parent->mainController->addEventToQueue(Command_c(string("attack ") + command->args[1].first + " " + command->args[2].first));
}

void ConsoleCommandController::exitGameCommand(Command_c* command, Obj* oParent) {
	ConsoleCommandController* parent = dynamic_cast<ConsoleCommandController*>(oParent);
	if (!parent) {
		throw new exception("Bad input class type");
	}
	Command_c tempEvent("exitgame");
	parent->mainController->addEventToQueue(tempEvent);
	defaultConsole->message("Exiting game");
}

void ConsoleCommandController::saveGameCommand(Command_c* command, Obj* oParent) {
	ConsoleCommandController* parent = dynamic_cast<ConsoleCommandController*>(oParent);
	if (!parent) {
		throw new exception("Bad input class type");
	}
	Command_c tempEvent(string("save game ") + command->args[2].first);
	parent->mainController->addEventToQueue(tempEvent);
}

void ConsoleCommandController::loadGameCommand(Command_c* command, Obj* oParent) {
	ConsoleCommandController* parent = dynamic_cast<ConsoleCommandController*>(oParent);
	if (!parent) {
		throw new exception("Bad input class type");
	}
	Command_c tempEvent(string("load game ") + command->args[2].first);
	parent->mainController->addEventToQueue(tempEvent);
}

void ConsoleCommandController::spawnUnitPresetCommand(Command_c * command, Obj * oParent) {
	ConsoleCommandController* parent = dynamic_cast<ConsoleCommandController*>(oParent);
	if (!parent) {
		throw new exception("Bad input class type");
	}
	Command_c tempEvent(string("spawn team ") + command->args[2].first + " unit " + command->args[4].first + " " + command->args[5].first + " " + command->args[6].first);
	parent->mainController->addEventToQueue(tempEvent);
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


