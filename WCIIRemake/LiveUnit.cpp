#include "pch.h"
#include "LiveUnit.h"

const int TimeoutTimes = 200;
extern Controller* gameController;


LiveUnit::LiveUnit(char value, int type, Field* field, int health, int team, int attackLength) {
	this->team = team;
	this->attackLength = attackLength;
	this->value = value;
	this->field = field;
	this->type = type;
	this->threadFlag = false;
	this->health = health;
}

LiveUnit::~LiveUnit() {

}


/*
bool LiveUnit::goTo(cordScr* dest) {
	threadFlag = true;

	FastPath* fastpath = new FastPath(this->field, this);
	int timeoutCounter = 0;
	while (timeoutCounter <= TimeoutTimes && this->health > 0) {
		int direction = fastpath->solveDirection(*dest);
		//		cout << "Unit '" << this->value << "' direction " << direction << endl;
		if (direction == -1) {
			break;
		}
		if (direction == 0) {
			//cout << "direction '" << value << "' = " << direction << endl;
			timeoutCounter++;
			Sleep(100);
		}
		else {
			timeoutCounter = 0;
			move(direction);
			srand(time(NULL));
			Sleep(300 + rand() % 20); //TODO: change to his speed
		}
	}


	cout << "Unit '" << this->value << "' finished movement" << endl;

	delete fastpath;

	threadFlag = false;
	return true;
}

*/

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

/*
void LiveUnit::threadFunction() {
	goTo(&moveDest);
}
*/

bool LiveUnit::classifyEvent(Command_c command) {
	if (command == "select") {
		return selectEvent(command);
	}


	if (command == "echo" && this->selected) {
		return echoEvent(command);
	}

	if (command == "tp" && this->selected) {
		return tpEvent(command);
	}

	if (command == "move") {
		return moveEvent(command);
	}

	if (command == "damage") {
		return damageEvent(command);
	}


	return false;
}

void LiveUnit::operateEvent(Command_c command)
{
	classifyEvent(command);
}



//LIVEUNIT COMMANDS(EVENTS)

bool LiveUnit::tpEvent(Command_c command) {
	if (command.args.size() == 3) {
		if (command.args[1].second == "number" && command.args[2].second == "number") {
			cordScr cords(stoi(command.args[1].first), stoi(command.args[2].first));
			return field->changeCell(cords, this);
		}
	}
	return false;
}

bool LiveUnit::moveEvent(Command_c command) {
	if (command.args.size() == 4) {
		if (command.args[1].first == "to" && command.args[2].second == "number" && command.args[3].second == "number" && this->selected) {
			this->moveDest = cordScr(stoi(command.args[2].first), stoi(command.args[3].first));
			if (!threadFlag) {
				//startThread();
			}
		}
	}
	return false;
}

