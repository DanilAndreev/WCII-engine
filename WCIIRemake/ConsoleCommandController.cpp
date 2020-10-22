#include "pch.h"
#include "ConsoleCommandController.h"


extern Console* defaultConsole;
extern Controller* gameController;
extern ThreadDescriptor* gameThreads;

ConsoleCommandController::ConsoleCommandController(Console* ioconsole, Controller* mainController, int team) {
	this->commandInput = true;
	this->team = team;
	this->fillCommandPatterns();
	this->fillEventPatterns();

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

void ConsoleCommandController::setTeam(int newteam) {
	this->team = newteam;
}

Command_c ConsoleCommandController::getCommand() {
	string command;
	command = console->getLine();
	return parseCommand(command);
}

KeyID ConsoleCommandController::getKey() {
	KeyID keyID = this->console->readKey();
	return keyID;
}

void ConsoleCommandController::switchUI() {
	this->commandInput = this->commandInput == true ? false : true;
}

void ConsoleCommandController::throwCommand(Command_c* command) { //--------------------------------------------------------------MODIFIED
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
	const ConsoleCommandPattern selectCordsAreaPattern(
		"select area input_number input_number input_number input_number",
		"selectCordsAreaPattern",
		"select area [int:x1] [int:y1] [int:x2] [int:y2]",
		ConsoleCommandController::selectCordsAreaCommand);
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
	const ConsoleCommandPattern spawnEnviromentPresetPattern(
		"spawn team input_number enviroment input_command input_number input_number",
		"spawnEnviromentPresetPattern",
		"spawn team [int:team] enviroment [string:unit name] [int:x] [int:y]",
		ConsoleCommandController::spawnEnviromentPresetCommand);
	const ConsoleCommandPattern stopUnitsPattern(
		"stop units",
		"stopUnitsPattern",
		"stop units",
		ConsoleCommandController::stopUnitsCommand);
	const ConsoleCommandPattern changTeamPattern(
		"change team input_number",
		"changTeamPattern",
		"change team [int:team]",
		ConsoleCommandController::changTeamCommand);
	const ConsoleCommandPattern renderScreenPattern(
		"render screen",
		"renderScreenPattern",
		"render screen {flags}",
		ConsoleCommandController::renderScreenCommand);
	const ConsoleCommandPattern switchUIPattern(
		"switch ui",
		"switchUIPattern",
		"switch ui",
		ConsoleCommandController::switchUICommand);
	const ConsoleCommandPattern clearConsolePattern(
		"clear console",
		"clearConsolePattern",
		"clear console",
		ConsoleCommandController::clearConsoleCommand);
	const ConsoleCommandPattern refreshInputsPattern(
		"refresh inputs",
		"refreshInputsPattern",
		"refresh inputs",
		ConsoleCommandController::refreshInputsCommand);
	const ConsoleCommandPattern newFieldPattern(
		"create field input_command input_number input_number",
		"newFieldPattern",
		"create field [string:name] [int:width] [int:heigth]",
		ConsoleCommandController::newFieldCommand);
	const ConsoleCommandPattern setupSpawnerPattern(
		"setup spawner input_command input_command team input_number",
		"setupSpawnerPattern",
		"setup spawner [string:preset type] [string:preset name] team [int:team]",
		ConsoleCommandController::setupSpawnerCommand);


	this->commandPatterns.push_back(selectCordsPattern);
	this->commandPatterns.push_back(selectSymbPattern);
	this->commandPatterns.push_back(selectIdPattern);
	this->commandPatterns.push_back(moveToPattern);
	this->commandPatterns.push_back(attackCordsPattern);
	this->commandPatterns.push_back(exitGamePattern);
	this->commandPatterns.push_back(saveGamePattern);
	this->commandPatterns.push_back(loadGamePattern);
	this->commandPatterns.push_back(spawnUnitPresetPattern);
	this->commandPatterns.push_back(spawnEnviromentPresetPattern);
	this->commandPatterns.push_back(selectCordsAreaPattern);
	this->commandPatterns.push_back(stopUnitsPattern);
	this->commandPatterns.push_back(changTeamPattern);
	this->commandPatterns.push_back(switchUIPattern);
	this->commandPatterns.push_back(clearConsolePattern);
	this->commandPatterns.push_back(refreshInputsPattern);
	this->commandPatterns.push_back(newFieldPattern);
	this->commandPatterns.push_back(setupSpawnerPattern);


	this->commandPatterns.push_back(renderScreenPattern);
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

void ConsoleCommandController::catchEvent(Command_c* command, bool showHelp) {
	this->operateEvent(command, showHelp);
}

//CONSOLE COMMAND CONTROLLER COMMANDS Fuctions
	
// select [int:x] [int:y]
void ConsoleCommandController::selectCordsCommand(Command_c* command, CommandPatterns* oParent) {
	ConsoleCommandController* parent = dynamic_cast<ConsoleCommandController*>(oParent);
	if (!parent) {
		throw new exception("Bad input class type");
	}
	int input_cord_x = 0;
	int input_cord_y = 0;
	try {
		input_cord_x = stoi(command->args[1].first);
		input_cord_y = stoi(command->args[2].first);
	}
	catch (...) {
		return;
	}
	cordScr input_cord(input_cord_x, input_cord_y);

	Command_c objectsInfoEvent(Command_c(string("get team ") + to_string(parent->team) + " info units"));
	parent->mainController->throwCommand(&objectsInfoEvent);
	

	Command_c clearSelectionInfoEvent(Command_c(string("select team ") + to_string(parent->team) + " -cl"));
	parent->mainController->throwCommand(&clearSelectionInfoEvent);
	for (int i = 0; i < objectsInfoEvent.data.size(); i++) {
		eventReturnDataUnitInfo* temp = dynamic_cast<eventReturnDataUnitInfo*>(objectsInfoEvent.data[i]);
		if (temp) {
			if (temp->cords == input_cord && temp->team == parent->team) {
				ID temp_id = temp->objId;
				Command_c tempEvent(Command_c(string("select team ") + to_string(parent->team) + " id " + to_string(temp_id)));
				parent->mainController->addEventToQueue(tempEvent);
			}
		}
	}
}



bool cordInArea(cordScr area_cord_1, cordScr area_cord_2, cordScr target_cord) {
	if (area_cord_1 <= area_cord_2 ) {
		return area_cord_1 <= target_cord && target_cord <= area_cord_2;
	}
	if (area_cord_2 <= area_cord_1) {
		return cordInArea(area_cord_2, area_cord_1, target_cord);
	}
	if (area_cord_1.x <= area_cord_2.x && area_cord_1.y >= area_cord_2.y) {
		return area_cord_1.x <= target_cord.x && target_cord.x <= area_cord_2.x && area_cord_2.y <= target_cord.y && target_cord.y <= area_cord_1.y;
	}
	if (area_cord_2.x <= area_cord_1.x && area_cord_2.y >= area_cord_1.y) {
		return cordInArea(area_cord_2, area_cord_1, target_cord);
	}
	return false;
}

// select area [int:x1] [int:y1] [int:x2] [int:y2]
void ConsoleCommandController::selectCordsAreaCommand(Command_c* command, CommandPatterns* oParent) {
	ConsoleCommandController* parent = dynamic_cast<ConsoleCommandController*>(oParent);
	if (!parent) {
		throw new exception("Bad input class type");
	}
	int input_cord_x1 = 0;
	int input_cord_y1 = 0;
	int input_cord_x2 = 0;
	int input_cord_y2 = 0;
	try {
		input_cord_x1 = stoi(command->args[2].first);
		input_cord_y1 = stoi(command->args[3].first);
		input_cord_x2 = stoi(command->args[4].first);
		input_cord_y2 = stoi(command->args[5].first);
	}
	catch (...) {
		return;
	}
	cordScr input_cord_1(input_cord_x1, input_cord_y1);
	cordScr input_cord_2(input_cord_x2, input_cord_y2);

	Command_c objectsInfoEvent(Command_c(string("get team ") + to_string(parent->team) + " info units"));
	parent->mainController->throwCommand(&objectsInfoEvent);

	Command_c clearSelectionInfoEvent(Command_c(string("select team ") + to_string(parent->team) + " -cl"));
	parent->mainController->throwCommand(&clearSelectionInfoEvent);

	for (int i = 0; i < objectsInfoEvent.data.size(); i++) {
		eventReturnDataUnitInfo* temp = dynamic_cast<eventReturnDataUnitInfo*>(objectsInfoEvent.data[i]);
		if (temp) {
			if (cordInArea(input_cord_1, input_cord_2, temp->cords) && temp->team == parent->team && temp->health > 0) {
				ID temp_id = temp->objId;
				Command_c tempEvent(Command_c(string("select team ") + to_string(parent->team) + " id " + to_string(temp_id)));
				parent->mainController->addEventToQueue(tempEvent);
			}
		}
	}
}



// select [char:symbol]
void ConsoleCommandController::selectSymbCommand(Command_c* command, CommandPatterns* oParent) {
	ConsoleCommandController* parent = dynamic_cast<ConsoleCommandController*>(oParent);
	if (!parent) {
		throw new exception("Bad input class type");
	}
	string input_symbol = command->args[1].first;

	Command_c objectsInfoEvent(Command_c(string("get team ") + to_string(parent->team) + " info units"));
	parent->mainController->throwCommand(&objectsInfoEvent);

	Command_c clearSelectionInfoEvent(Command_c(string("select team ") + to_string(parent->team) + " -cl"));
	parent->mainController->throwCommand(&clearSelectionInfoEvent);

	for (int i = 0; i < objectsInfoEvent.data.size(); i++) {
		eventReturnDataUnitInfo* temp = dynamic_cast<eventReturnDataUnitInfo*>(objectsInfoEvent.data[i]);
		if (temp) {
			if (temp->valueVariable == input_symbol && temp->team == parent->team && temp->health > 0) {
				ID temp_id = temp->objId;
				Command_c tempEvent(Command_c(string("select team ") + to_string(parent->team) + " id " + to_string(temp_id)));
				parent->mainController->addEventToQueue(tempEvent);
			}
		}
	}
}

// select [int:id]
void ConsoleCommandController::selectIdCommand(Command_c* command, CommandPatterns* oParent) {
	ConsoleCommandController* parent = dynamic_cast<ConsoleCommandController*>(oParent);
	if (!parent) {
		throw new exception("Bad input class type");
	}
	ID input_ID = 0;
	try {
		input_ID = stoull(command->args[1].first);
	}
	catch (...) {
		return;
	}

	Command_c objectsInfoEvent(Command_c(string("get team ") + to_string(parent->team) + " info units"));
	parent->mainController->throwCommand(&objectsInfoEvent);

	Command_c clearSelectionInfoEvent(Command_c(string("select team ") + to_string(parent->team) + " -cl"));
	parent->mainController->throwCommand(&clearSelectionInfoEvent);

	for (int i = 0; i < objectsInfoEvent.data.size(); i++) {
		eventReturnDataUnitInfo* temp = dynamic_cast<eventReturnDataUnitInfo*>(objectsInfoEvent.data[i]);
		if (temp) {
			if (temp->objId == input_ID && temp->team == parent->team && temp->health > 0) {
				ID temp_id = temp->objId;
				Command_c tempEvent(Command_c(string("select team ") + to_string(parent->team) + " id " +  to_string(temp_id)));
				parent->mainController->addEventToQueue(tempEvent);
			}
		}
	}
}


// move to [int:x] [int:y]
void ConsoleCommandController::moveToCommand(Command_c* command, CommandPatterns* oParent) {
	ConsoleCommandController* parent = dynamic_cast<ConsoleCommandController*>(oParent);
	if (!parent) {
		throw new exception("Bad input class type");
	}
	int input_cord_x = 0;
	int input_cord_y = 0;
	try {
		input_cord_x = stoi(command->args[2].first);
		input_cord_y = stoi(command->args[3].first);
	}
	catch (...) {
		return;
	}

	cordScr input_cord(input_cord_x, input_cord_y);

	Command_c objectsInfoEvent(Command_c(string("get team ") + to_string(parent->team) + " info units"));
	parent->mainController->throwCommand(&objectsInfoEvent);

	for (int i = 0; i < objectsInfoEvent.data.size(); i++) {
		eventReturnDataUnitInfo* temp = dynamic_cast<eventReturnDataUnitInfo*>(objectsInfoEvent.data[i]);
		if (temp) {
			if (temp->selected) {
				ID temp_id = temp->objId;
				Command_c tempEvent(Command_c(string("move id ") + to_string(temp_id) + " to " + to_string(input_cord.x) + " " + to_string(input_cord.y)));
				parent->mainController->addEventToQueue(tempEvent);
			}
		}
	}
}

// attack [int:x] [int:y]
void ConsoleCommandController::attackCordsCommand(Command_c* command, CommandPatterns* oParent) {
	ConsoleCommandController* parent = dynamic_cast<ConsoleCommandController*>(oParent);
	if (!parent) {
		throw new exception("Bad input class type");
	}
	int input_cord_x = 0;
	int input_cord_y = 0;
	try {
		input_cord_x = stoi(command->args[1].first);
		input_cord_y = stoi(command->args[2].first);
	}
	catch (...) {
		return;
	}

	cordScr input_cord(input_cord_x, input_cord_y);

	Command_c objectsInfoEvent(Command_c(string("get team ") + to_string(parent->team) +" info units"));
	parent->mainController->throwCommand(&objectsInfoEvent);

	for (int i = 0; i < objectsInfoEvent.data.size(); i++) {
		eventReturnDataUnitInfo* temp = dynamic_cast<eventReturnDataUnitInfo*>(objectsInfoEvent.data[i]);
		if (temp) {
			if (temp->selected) {
				ID temp_id = temp->objId;
				Command_c tempEvent(Command_c(string("attack id ") + to_string(temp_id) + " to " + to_string(input_cord.x) + " " + to_string(input_cord.y)));
				parent->mainController->addEventToQueue(tempEvent);
			}
		}
	}
}

// exit game
void ConsoleCommandController::exitGameCommand(Command_c* command, CommandPatterns* oParent) {
	ConsoleCommandController* parent = dynamic_cast<ConsoleCommandController*>(oParent);
	if (!parent) {
		throw new exception("Bad input class type");
	}
	Command_c tempEvent("exitgame");
	parent->mainController->addEventToQueue(tempEvent);
	parent->console->message("Exiting game");
}

// save game [string:savename]
void ConsoleCommandController::saveGameCommand(Command_c* command, CommandPatterns* oParent) {
	ConsoleCommandController* parent = dynamic_cast<ConsoleCommandController*>(oParent);
	if (!parent) {
		throw new exception("Bad input class type");
	}
	Command_c tempEvent(string("save game ") + command->args[2].first);
	parent->mainController->addEventToQueue(tempEvent);
}

// load game [string:savename]
void ConsoleCommandController::loadGameCommand(Command_c* command, CommandPatterns* oParent) {
	ConsoleCommandController* parent = dynamic_cast<ConsoleCommandController*>(oParent);
	if (!parent) {
		throw new exception("Bad input class type");
	}
	Command_c tempEvent(string("load game ") + command->args[2].first);
	parent->mainController->addEventToQueue(tempEvent);
}

// spawn team [int:team] unit [string:unit name] [int:x] [int:y]
void ConsoleCommandController::spawnUnitPresetCommand(Command_c * command, CommandPatterns* oParent) {
	ConsoleCommandController* parent = dynamic_cast<ConsoleCommandController*>(oParent);
	if (!parent) {
		throw new exception("Bad input class type");
	}
	Command_c tempEvent(string("spawn team ") + command->args[2].first + " unit " + command->args[4].first + " cords " + command->args[5].first + " " + command->args[6].first);
	parent->mainController->addEventToQueue(tempEvent);
}

// spawn team [int:team] enviroment [string:unit name] [int:x] [int:y]
void ConsoleCommandController::spawnEnviromentPresetCommand(Command_c* command, CommandPatterns* oParent) {
	ConsoleCommandController* parent = dynamic_cast<ConsoleCommandController*>(oParent);
	if (!parent) {
		throw new exception("Bad input class type");
	}
	Command_c tempEvent(string("spawn team ") + command->args[2].first + " enviroment " + command->args[4].first + " cords " + command->args[5].first + " " + command->args[6].first);
	parent->mainController->addEventToQueue(tempEvent);
}

void ConsoleCommandController::stopUnitsCommand(Command_c* command, CommandPatterns* oParent) {
	ConsoleCommandController* parent = dynamic_cast<ConsoleCommandController*>(oParent);
	if (!parent) {
		throw new exception("Bad input class type");
	}
	Command_c objectsInfoEvent(Command_c(string("get team ") + to_string(parent->team) + " info units"));
	parent->mainController->throwCommand(&objectsInfoEvent);

	for (int i = 0; i < objectsInfoEvent.data.size(); i++) {
		eventReturnDataUnitInfo* temp = dynamic_cast<eventReturnDataUnitInfo*>(objectsInfoEvent.data[i]);
		if (temp) {
			if (temp->selected) {
				ID temp_id = temp->objId;
				Command_c tempEvent(Command_c(string("stop id ") + to_string(temp_id) + " movement"));
				parent->mainController->addEventToQueue(tempEvent);
			}
		}
	}

}
// change team [int:team]
void ConsoleCommandController::changTeamCommand(Command_c* command, CommandPatterns* oParent) {
	ConsoleCommandController* parent = dynamic_cast<ConsoleCommandController*>(oParent);
	if (!parent) {
		throw new exception("Bad input class type");
	}
	int input_team = 1;
	try {
		input_team = stoi(command->args[2].first);
	}
	catch (...) {
		return;
	}
	parent->setTeam(input_team);
	parent->console->message("Interface changed for team: " + to_string(input_team));
}

void ConsoleCommandController::renderScreenCommand(Command_c* command, CommandPatterns* oParent) {
	ConsoleCommandController* parent = dynamic_cast<ConsoleCommandController*>(oParent);
	if (!parent) {
		throw new exception("Bad input class type");
	}
	Command_c tempEvent(*command);
	parent->mainController->addEventToQueue(tempEvent);
}

// switch ui
void ConsoleCommandController::switchUICommand(Command_c * command, CommandPatterns * oParent) {
	ConsoleCommandController* parent = dynamic_cast<ConsoleCommandController*>(oParent);
	if (!parent) {
		throw new exception("Bad input class type");
	}
//	parent->commandInput = parent->commandInput == true ? false : true;
	parent->switchUI();
	parent->console->message("Switched UI");
}

void ConsoleCommandController::clearConsoleCommand(Command_c* command, CommandPatterns* oParent) {
	ConsoleCommandController* parent = dynamic_cast<ConsoleCommandController*>(oParent);
	if (!parent) {
		throw new exception("Bad input class type");
	}
	parent->console->clearScreen();
}

// refresh inputs
void ConsoleCommandController::refreshInputsCommand(Command_c* command, CommandPatterns* oParent) {
	ConsoleCommandController* parent = dynamic_cast<ConsoleCommandController*>(oParent);
	if (!parent) {
		throw new exception("Bad input class type");
	}
	Command_c tempEvent(Command_c(string("refresh inputs")));
	parent->mainController->addEventToQueue(tempEvent);
}

// create field [string:name] [int:width] [int:heigth]
void ConsoleCommandController::newFieldCommand(Command_c* command, CommandPatterns* oParent) {
	ConsoleCommandController* parent = dynamic_cast<ConsoleCommandController*>(oParent);
	if (!parent) {
		throw new exception("Bad input class type");
	}
	int input_width = 10;
	int input_height = 10;
	try {
		input_width = stoi(command->args[3].first);
		input_height = stoi(command->args[4].first);
	}
	catch (...) {
		return;
	}

	string filename = command->args[2].first;
	string path = "saves/";
	path += filename + ".wcsave";
	FileWriter* writer = new FileWriter(path, ios::out);
	*writer << "save " << filename << endl;
	*writer << "field { width: " << input_width << "; heigth: " << input_height << "; }" << endl;
	delete writer;
	
	parent->console->message("Creating field " + filename + ", ratio: " + to_string(input_width) + " " + to_string(input_height));

	Command_c tempEvent(Command_c(string("load game ") + filename + " -noInfo"));
	parent->mainController->addEventToQueue(tempEvent);
}

// setup spawner [string:preset type] [string:preset name] team [int:team]
void ConsoleCommandController::setupSpawnerCommand(Command_c* command, CommandPatterns* oParent) {
	ConsoleCommandController* parent = dynamic_cast<ConsoleCommandController*>(oParent);
	if (!parent) {
		throw new exception("Bad input class type");
	}
	int input_team = 1;
	try {
		input_team = stoi(command->args[5].first);
	}
	catch (...) {
		return;
	}
	string input_preset_type = command->args[2].first;
	string input_preset_name = command->args[3].first;

	Command_c tempEvent(Command_c(string("setup spawner ") + input_preset_type + " " + input_preset_name + " team " + to_string(input_team) + " CCC id " + to_string(parent->id)));
	parent->mainController->addEventToQueue(tempEvent);
}


// EVENT HANDLING SYSTEM

void ConsoleCommandController::fillEventPatterns() {
	const EventPattern exitGamePattern(
		"exitgame",
		"exitGamePattern",
		"exitgame",
		ConsoleCommandController::exitGameCommand);
	const EventPattern stopThreadsPattern(
		"stop threads",
		"getInfoTeamUnitsPattern",
		"stop threads {flags}",
		ConsoleCommandController::stopThreadsCommand);
	const EventPattern pausePattern(
		"pause",
		"getInfoTeamUnitsPattern",
		"pause {flags}",
		ConsoleCommandController::pauseCommand);
	const EventPattern unpausePattern(
		"unpause",
		"getInfoTeamUnitsPattern",
		"unpause {flags}",
		ConsoleCommandController::unpauseCommand);
	const EventPattern keyPressIdPattern(
		"key pressed id input_number CCC id input_number",
		"keyPressIdPattern",
		"key pressed id [int:keyid] CCC id [int:ConsoleCommandControllerId]",
		ConsoleCommandController::keyPressIdCommand);

	this->eventPatterns.push_back(exitGamePattern);
	this->eventPatterns.push_back(stopThreadsPattern);
	this->eventPatterns.push_back(pausePattern);
	this->eventPatterns.push_back(unpausePattern);
	this->eventPatterns.push_back(keyPressIdPattern);
}

//CONSOLE COMMAND CONTROLLER EVENTS

// exitgame
void ConsoleCommandController::exitGameCommand(Command_c* command, Eventable* oParent) {
	ConsoleCommandController* parent = dynamic_cast<ConsoleCommandController*>(oParent);
	if (!parent) {
		return;
	}
	gameThreads->stopThread(parent->ConComConTHRDescriptor);
}

// stop threads {flags}
void ConsoleCommandController::stopThreadsCommand(Command_c* command, Eventable* oParent) {
	ConsoleCommandController* parent = dynamic_cast<ConsoleCommandController*>(oParent);
	if (!parent) {
		return;
	}
	if (!command->checkFlag("-ccc")) {
		HANDLE temp_handle;
		if ((temp_handle = gameThreads->stopThread(parent->ConComConTHRDescriptor)) != NULL) {
			eventReturnDataHandle* temp =  new eventReturnDataHandle(parent->id, parent->className, temp_handle);
			command->data.push_back(temp);
		}

		fprintf(stdin, "\n");
	}
}

// pause {flags}
void ConsoleCommandController::pauseCommand(Command_c* command, Eventable* oParent) {
	ConsoleCommandController* parent = dynamic_cast<ConsoleCommandController*>(oParent);
	if (!parent) {
		return;
	}
	if (command->checkFlag("-command_input")) {
		parent->pause();
	}
}

// unpause {flags}
void ConsoleCommandController::unpauseCommand(Command_c* command, Eventable* oParent) {
	ConsoleCommandController* parent = dynamic_cast<ConsoleCommandController*>(oParent);
	if (!parent) {
		return;
	}
	if (command->checkFlag("-command_input")) {
		parent->unpause();
	}
}

void ConsoleCommandController::keyPressIdCommand(Command_c * command, Eventable * oParent) {
	ConsoleCommandController* parent = dynamic_cast<ConsoleCommandController*>(oParent);
	if (!parent) {
		return;
	}
	int input_keyid = 0;
	ID input_cccid = 0;
	try {
		input_keyid = stoi(command->args[3].first);
		input_cccid = stoull(command->args[6].first);
	}
	catch (...) {
		return;
	}
	if (input_cccid == parent->id) {
		switch (input_keyid) {
		case 9: // tab
			parent->switchUI();
			break;
		}
	}

}

