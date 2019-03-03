#include "pch.h"
#include "Unit.h"

const int TimeoutTimes = 200;

/*
Unit::Unit(Unit** field) {
	this->field = field;
}


Unit::Unit() {
	Unit(NULL);
}
*/
Unit::Unit(cordScr cords, char value,int type, Field* field) {
	this->cords = cords;
	this->value = value;
	this->field = field;
	this->type = type;
	this->threadFlag = false;

}



Unit::~Unit() {

}

int Unit::getType() {
	return this->type;
}

char Unit::getValue() {
	return value;
}

int Unit::move(int direction) {
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
			if (field->changeCell(cordScr(cords.x + 1 , cords.y + 1), this)) {
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

bool Unit::goTo(cordScr* dest) {
	threadFlag = true;

	FastPath* fastpath = new FastPath(this->field, this);
	int timeoutCounter = 0;
	while (timeoutCounter <= TimeoutTimes) {
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
			Sleep(300 + rand()%20); //TODO: change to his speed
		}
	}


	cout << "Unit '" << this->value << "' finished movement" << endl;

	delete fastpath;

	threadFlag = false;
	return true;
}

int Unit::findPath(cordScr destC) {

	return 0;
}


void Unit::render() {
	if (scr != NULL) {
		scr->putToBuff(this->cords, this->value);
	}
}

bool Unit::classifyEvent(Command_c command) {
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



	return false;
}

void Unit::threadFunction() {
	goTo(&moveDest);
}

void Unit::operateEvent(Command_c command)
{
//	cout << "Unit '" << value << "' operating event" << endl;
	classifyEvent(command);
}


//UNIT COMMANDS(EVENTS)
bool Unit::selectEvent(Command_c command) {
	if (command.args.size() == 2) {
		if (command.args[1].first == "all") {
			this->selected = true;
			cout << "Selected unit " << value << endl;
			return true;
		}
	}
	if (command.args.size() > 1) {
		for (int i = 1; i < command.args.size(); i++) {
			if (command.args[i].first[0] == this->value) {
				this->selected = true;
				cout << "Selected unit " << value << endl;
				return true;
			}
		}
		this->selected = false;
		return true;
	}
	return false;
}

bool Unit::echoEvent(Command_c command) {
	if (command.args.size() > 1) {
		string msg;
		for (int i = 1; i < command.args.size(); i++) {
			msg += command.args[i].first + " ";
		}
		cout << "Unit " << value << " say: " << msg << endl;
		return true;
	}
	return false;
}

bool Unit::tpEvent(Command_c command) {
	if (command.args.size() == 3) {
		if (command.args[1].second == "number" && command.args[2].second == "number") {
			cordScr cords(stoi(command.args[1].first), stoi(command.args[2].first));
			return field->changeCell(cords, this);
		}
	}
	return false;
}

bool Unit::moveEvent(Command_c command) {
	if (command.args.size() == 4) {
		if (command.args[1].first == "to" && command.args[2].second == "number" && command.args[3].second == "number" && this->selected) {
			this->moveDest = cordScr(stoi(command.args[2].first), stoi(command.args[3].first));
			if (!threadFlag) {
				startThread();
			}
		}
	}
	return false;
}

