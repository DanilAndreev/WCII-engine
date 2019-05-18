#include "pch.h"
#include "LiveUnit.h"

const int TimeoutTimes = 200;
extern Controller* gameController;
extern ThreadDescriptor* gameThreads;
extern ConsoleCommandController* defaultConComCon;
extern Console* defaultConsole;



LiveUnitPreset::LiveUnitPreset(string name, string beautyName, string fraction, char symbol, int width, int heigth, int health, int damage, int cooldown, int attackRadius, int speedDelay, int mana, vector<string> spells, int cost, int eats, int productionTime) {
	this->name = name;
	this->beautyName = beautyName;
	this->fraction = fraction;
	this->symbol = symbol;
	this->width = width;
	this->heigth = heigth;
	this->health = health;
	this->damage = damage;
	this->cooldown = cooldown;
	this->attackRadius = attackRadius;
	this->mana = mana;
	this->spells = spells;
	this->cost = cost;
	this->eats = eats;
	this->productionTime = productionTime;
	this->speedDelay = speedDelay;
}

LiveUnitPreset::~LiveUnitPreset()
{
}

void LiveUnitPreset::print() {
	cout << "unit: " << name << ", beauty name: " << beautyName << endl;
	cout << "fraction: " << fraction << endl;
	cout << "symbol: " << symbol << endl;
	cout << "width: " << width << endl;
	cout << "heigth: " << heigth << endl;
	cout << "health: " << health << endl;
	cout << "damage: " << damage << endl;
	cout << "cooldown: " << cooldown << endl;
	cout << "attackRadius: " << attackRadius << endl;
	cout << "mana: " << mana << endl;
	cout << "spells: [";
	for (int i = 0; i < spells.size(); i++) {
		cout << spells[i] << " "  ;
	}
	cout << "]" << endl;
	cout << "cost: " << cost << endl;
	cout << "eats: " << eats << endl;
	cout << "productionTime: " << productionTime << endl;
	cout << endl;
}






LiveUnit::LiveUnit(char value, int type, Field* field, int health, int team, int attackLength, time_t cooldown, time_t moveSpeed, int attackPower) : Unit(value, type, field, health, team) {
/*
	this->team = team;
	this->attackLength = attackLength;
	this->value = value;
	this->field = field;
	this->type = type;
	this->threadFlag = false;
	this->health = health;
*/
	this->fillCommandPatterns();
	setDescription("LiveUnit");
	this->attackLength = attackLength;
	this->MoveToTHRDDescriptor = 0;
	this->AttackTHRDDescriptor = 0;
	this->moveNoAttack = false;
	this->cooldown = cooldown;
	this->moveSpeed = moveSpeed;
	this->attackPower = attackPower;
}

LiveUnit::~LiveUnit() {

}

ThreadId LiveUnit::getMoveToTHRDDescriptor()
{
	return this->MoveToTHRDDescriptor;
}



bool LiveUnit::goTo(cordScr* dest, bool & flag) {
	threadFlag = true;

	FastPath* fastpath = new FastPath(this->field, this);
	int timeoutCounter = 0;
	while (flag && timeoutCounter <= TimeoutTimes && this->health > 0) {
		int direction = fastpath->solveDirection(*dest);
		if (direction == -1) {
			break;
		}
		if (direction == 0) {
			timeoutCounter++;
			Sleep(100);
		}
		else {
			timeoutCounter = 0;
			move(direction);
			srand(time(NULL));
			Sleep(this->moveSpeed + rand() % 20);
		}
	}
	delete fastpath;
	threadFlag = false;
	return true;
}

bool LiveUnit::attack(bool & flag) {
	DynArr* members = field->getMembers();
	for (int i = 0; i < members->count(); i++) {
		Unit* unt = (Unit*)(members->get(i));
		if (unt) {
			cordScr tarCords = ((Unit*)(members->get(i)))->getCord();
			if (this->cords.lineLength(this->cords, tarCords) <= this->attackLength && this->team != unt->getTeam() && unt->getHealth() > 0) {
				// generating the event for damage
/*
				Command_c command;
				pair <string, string> arg;
				arg.first = "damage";
				arg.second = "command";
				command.args.push_back(arg);
				arg.first = ((Unit*)(members->get(i)))->getValue();
				arg.second = "command";
				command.args.push_back(arg);
				arg.first = to_string(30); //TODO: add the damage value to unit!!!
				arg.second = "number";
				command.args.push_back(arg);
				gameController->addEventToQueue(command);
*/				
				string value = "";
				int id = ((Unit*)(members->get(i)))->getId();
				gameController->addEventToQueue(Command_c(0, "damage", to_string(id).data(), to_string(this->attackPower).data(), 0));
				this->lastAttackTime = clock();
				return true;
			}
		}
	}
	return false;
}

time_t LiveUnit::getLastAttackTime() {
	return this->lastAttackTime;
}

bool LiveUnit::setLastAttackTime(time_t iclock) {
	this->lastAttackTime = iclock;
	return true;
}

time_t LiveUnit::getCooldown() {
	return this->cooldown;
}



int LiveUnit::findPath(cordScr destC) {

	return 0;
}



int LiveUnit::move(int direction) {
	switch (direction) {
	case 1: // up
		if (field->changeCell(cordScr(cords.x, cords.y - 1), this)) {
			return 1;
		}
		break;
	case 2: // down
		if (field->changeCell(cordScr(cords.x, cords.y + 1), this)) {
			return 1;
		}
		break;
	case 3: // rigth
		if (field->changeCell(cordScr(cords.x + 1, cords.y), this)) {
			return 1;
		}
		break;
	case 4: // left
		if (field->changeCell(cordScr(cords.x - 1, cords.y), this)) {
			return 1;
		}
		break;
	case 5: // up right
		if (field->changeCell(cordScr(cords.x + 1, cords.y - 1), this)) {
			return 1;
		}
		break;
	case 6: // up left
		if (field->changeCell(cordScr(cords.x - 1, cords.y - 1), this)) {
			return 1;
		}
		break;
	case 7: // down right
		if (field->changeCell(cordScr(cords.x + 1, cords.y + 1), this)) {
			return 1;
		}
		break;
	case 8: // down left
		if (field->changeCell(cordScr(cords.x - 1, cords.y + 1), this)) {
			return 1;
		}
		break;
	}
	return 0;
}

cordScr * LiveUnit::getMoveDest() {
	return &moveDest;
}

bool LiveUnit::classifyEvent(Command_c* command) {
	if (*command == "select") {
		return selectEvent(command);
	}


	if (*command == "echo" && this->selected) {
		return echoEvent(command);
	}

	if (*command == "tp" && this->selected) {
		return tpEvent(command);
	}

	if (*command == "move" && this->selected) {
		return moveEvent(command);
	}

	if (*command == "damage") {
		return damageEvent(command);
	}

	if (*command == "attack" && this->selected) {
		return attackEvent(command);
	}

	if (*command == "stop" && this->selected) {
		return stopEvent(command);
	}
	
	if (*command == "getInfo") {
		return getInfoEvent(command);
	}

	if (*command == "write") {
		return writeEvent(command);
	}

	return false;
}

void LiveUnit::operateEvent(Command_c* command) {
//	classifyEvent(command);
	operateConsoleCommand(command, false);

}

void LiveUnit::stopAllThreads() {
	gameThreads->stopThread(AttackTHRDDescriptor);
	gameThreads->stopThread(MoveToTHRDDescriptor);
}

void LiveUnit::fillCommandPatterns() {
	const ConsoleCommandPattern tpToCordsPattern(
		"tp id input_number to input_number input_number",
		"tpToCordsPattern",
		"tp id [int:id] to [int:x] [int:y]",
		LiveUnit::tpToCordsCommand);
	const ConsoleCommandPattern moveToCordsPattern(
		"move id input_number to input_number input_number",
		"moveToCordsPattern",
		"move id [int:id] to [int:x] [int:y]",
		LiveUnit::moveToCordsCommand);
	const ConsoleCommandPattern stopThreadsPattern(
		"stop threads",
		"stopThreadsPattern",
		"stop threads",
		LiveUnit::stopThreadsCommand);
	const ConsoleCommandPattern attackToCordsPattern(
		"attack id input_number to input_number input_number",
		"attackToCordsPattern",
		"attack id [int:id] to [int:x] [int:y]",
		LiveUnit::attackToCordsCommand);
	const ConsoleCommandPattern writeToPattern(
		"write data to input_command",
		"writeToPattern",
		"write data to [string:filename]",
		LiveUnit::writeToCommand);

	this->commandPatterns.push_back(tpToCordsPattern);
	this->commandPatterns.push_back(moveToCordsPattern);
	this->commandPatterns.push_back(stopThreadsPattern);
	this->commandPatterns.push_back(attackToCordsPattern);
	this->commandPatterns.push_back(writeToPattern);
}

// tp id [int:id] to [int:x] [int:y]
void LiveUnit::tpToCordsCommand(Command_c* command, CommandPatterns* oParent) {
	LiveUnit* parent = dynamic_cast<LiveUnit*>(oParent);
	if (!parent) {
		return;
	}
	ID input_id = 0;
	int input_cord_x = 0;
	int input_cord_y = 0;
	try {
		input_id = stoull(command->args[2].first);
		input_cord_x = stoi(command->args[4].first);
		input_cord_y = stoi(command->args[5].first);
	}
	catch (...) {
		return;
	}
	if (parent->id == input_id) {
		cordScr cords(input_cord_x, input_cord_y);
		parent->field->changeCell(cords, parent);
	}
}

// move id [int:id] to [int:x] [int:y]
void LiveUnit::moveToCordsCommand(Command_c* command, CommandPatterns* oParent) {
	LiveUnit* parent = dynamic_cast<LiveUnit*>(oParent);
	if (!parent) {
		return;
	}
	ID input_id = 0;
	int input_cord_x = 0;
	int input_cord_y = 0;
	try {
		input_id = stoull(command->args[2].first);
		input_cord_x = stoi(command->args[4].first);
		input_cord_y = stoi(command->args[5].first);
	}
	catch (...) {
		return;
	}
	if (parent->id == input_id) {
		parent->moveDest = cordScr(input_cord_x, input_cord_y);
		gameThreads->stopThread(parent->AttackTHRDDescriptor);
		AttackTHREAD* attackTHRD = new AttackTHREAD(parent);
		if (attackTHRD) {
			parent->AttackTHRDDescriptor = attackTHRD->getDescriptor();
		}
		else {
			defaultConsole->error("Error allocating memory");
		}
		parent->moveNoAttack = true;
		attackTHRD->startThread();
	}
}

// attack id [int:id] to [int:x] [int:y]
void LiveUnit::attackToCordsCommand(Command_c* command, CommandPatterns* oParent) {
	LiveUnit* parent = dynamic_cast<LiveUnit*>(oParent);
	if (!parent) {
		return;
	}
	ID input_id = 0;
	int input_cord_x = 0;
	int input_cord_y = 0;
	try {
		input_id = stoull(command->args[2].first);
		input_cord_x = stoi(command->args[4].first);
		input_cord_y = stoi(command->args[5].first);
	}
	catch (...) {
		return;
	}
	if (parent->id == input_id) {
		parent->moveDest = cordScr(input_cord_x, input_cord_y);
		//starting attack thread
		gameThreads->stopThread(parent->AttackTHRDDescriptor);
		AttackTHREAD* attackTHRD = new AttackTHREAD(parent);
		if (attackTHRD) {
			parent->AttackTHRDDescriptor = attackTHRD->getDescriptor();
		}
		else {
			defaultConsole->error("Error allocating memory");
		}
		attackTHRD->startThread();
		cout << "unit: " << parent->id << " attacking" << endl;
	}
}

// stop threads
void LiveUnit::stopThreadsCommand(Command_c* command, CommandPatterns* oParent) {
	LiveUnit* parent = dynamic_cast<LiveUnit*>(oParent);
	if (!parent) {
		return;
	}
	HANDLE temp_handle;
	if ((temp_handle = gameThreads->stopThread(parent->MoveToTHRDDescriptor)) != NULL) {
		command->data.push_back(temp_handle);
	}
	if ((temp_handle = gameThreads->stopThread(parent->AttackTHRDDescriptor)) != NULL) {
		command->data.push_back(temp_handle);
	}
}

//write data to [string:filename]
void LiveUnit::writeToCommand(Command_c* command, CommandPatterns* oParent) {
	LiveUnit* parent = dynamic_cast<LiveUnit*>(oParent);
	if (!parent) {
		return;
	}
	string filename = command->args[3].first;
	FileWriter writer(filename, ios::app);
	writer << " unit {";
	writer << " x:" << parent->cords.x << ";";
	writer << " y:" << parent->cords.y << ";";
	writer << " symbol:\'" << parent->value << "\';";
	writer << " width:" << parent->width << ";";
	writer << " heigth:" << parent->heigth << ";";
	writer << " health:" << parent->health << ";";
	writer << " damage:" << parent->attackPower << ";";
	writer << " cooldown:" << parent->cooldown << ";";
	writer << " attackRadius:" << parent->attackLength << ";";
	writer << " speedDelay:" << parent->moveSpeed << ";";
	//writer << "mana:" << parent->mana << ";";
	writer << "}" << endl;
}

//LIVEUNIT COMMANDS(EVENTS)

bool LiveUnit::tpEvent(Command_c* command) {
	if (command->args.size() == 3) {
		if (command->args[1].second == "number" && command->args[2].second == "number") {
			cordScr cords(stoi(command->args[1].first), stoi(command->args[2].first));
			return field->changeCell(cords, this);
		}
	}
	return false;
}

bool LiveUnit::moveEvent(Command_c* command) {
	if (command->args.size() == 4) {
		if (command->args[1].first == "to" && command->args[2].second == "number" && command->args[3].second == "number" && this->selected) {
			this->moveDest = cordScr(stoi(command->args[2].first), stoi(command->args[3].first));


			gameThreads->stopThread(AttackTHRDDescriptor);
			AttackTHREAD* attackTHRD = new AttackTHREAD(this);
			if (attackTHRD) {
				this->AttackTHRDDescriptor = attackTHRD->getDescriptor();
			}
			else {
				//cout << "Error allocating memory" << endl;
				defaultConsole->error("Error allocating memory");
			}
			this->moveNoAttack = true;
			attackTHRD->startThread();
		}
	}
	return false;
}

bool LiveUnit::attackEvent(Command_c* command) {
	if (command->args.size() == 3) {
		if (command->args[1].second == "number" && command->args[2].second == "number") {
			this->moveDest = cordScr(stoi(command->args[1].first), stoi(command->args[2].first));
			//starting attack thread
			gameThreads->stopThread(AttackTHRDDescriptor);
			AttackTHREAD* attackTHRD = new AttackTHREAD(this);
			if (attackTHRD) {
				this->AttackTHRDDescriptor = attackTHRD->getDescriptor();
			}
			else {
				defaultConsole->error("Error allocating memory");
			}
			attackTHRD->startThread();
		}
	}
	return false;
}


bool LiveUnit::stopEvent(Command_c* command) {
	if (command->args.size() >= 2) {
		if (command->args[1].first == "threads" && command->args[1].second == "command") {
			HANDLE temp_handle;
			if ( (temp_handle = gameThreads->stopThread(MoveToTHRDDescriptor)) != NULL ) {
				command->data.push_back(temp_handle);
			}
			if ((temp_handle = gameThreads->stopThread(AttackTHRDDescriptor)) != NULL) {
				command->data.push_back(temp_handle);
			}
			return true;
		}
	}
	return false;
}

bool LiveUnit::writeEvent(Command_c* command) {
	if (command->args.size() >= 3) {
		if (command->args[0].second == "command" && command->args[1].second == "command" && command->args[2].second == "command" && command->args[3].second == "command") {
			if (command->args[1].first == "data" && command->args[2].first == "to") {
				FileWriter writer(command->args[3].first, ios::app);
				writer << " unit {";
				writer << " x:" << this->cords.x << ";";
				writer << " y:" << this->cords.y << ";";
				writer << " symbol:\'" << this->value << "\';";
				writer << " width:" << this->width << ";";
				writer << " heigth:" << this->heigth << ";";
				writer << " health:" << this->health << ";";
				writer << " damage:" << this->attackPower << ";";
				writer << " cooldown:" << this->cooldown<< ";";
				writer << " attackRadius:" << this->attackLength << ";";
				writer << " speedDelay:" << this->moveSpeed << ";";
//				writer << "mana:" << this->mana << ";";
				writer << "}" << endl;
				return true;
			}
		}
	}
	return false;
}
