#include "pch.h"
#include "CS_Selector.h"

extern ConsoleCommandController* defaultConComCon;


CS_Selector::CS_Selector(ID CccID, EV_CScreen_Controlled* icontrolledScreen) : Placable(cordScr(3,3), 1000) {
	this->fillEventPatterns();
	this->symbol = CScreenPixel('+', COLOR_BLUE);
	this->ConComConId = CccID;
	this->controlledScreen = icontrolledScreen;
	this->cordFix1 = cordScr(0, 0);
	this->cordFix2 = cordScr(0, 0);
	this->operation = SELECTOR_ATTACK;
	this->selectingFirst = true;
}

CS_Selector::~CS_Selector() {
}

void CS_Selector::setCCCID(ID CccID) {
	this->ConComConId = CccID;
}

void CS_Selector::render(int layer) {
	this->parentScreen->putToBuff(this->cords, this->symbol);
}

void CS_Selector::render() {
	render(0);
}

cordScr CS_Selector::calculateSelectorCordOnControlled() {
	cordScr contrlScreenCords = controlledScreen->getCords();
	return  this->cords - contrlScreenCords;
}

void CS_Selector::select() {
	if (selectingFirst) {
		cordFix1 = calculateSelectorCordOnControlled();
	}
	else {
		cordFix2 = calculateSelectorCordOnControlled();
	}
	if (!selectingFirst) {
		Command_c* command_c = new Command_c(string("select area " + to_string(cordFix1.x) + " " + to_string(cordFix1.y) + " " + to_string(cordFix2.x) + " " + to_string(cordFix2.y)));
		//command_c->printCommand();
		if (!command_c) {
			return;
		}
		defaultConComCon->throwCommand(command_c);
		delete command_c;

	}
	this->selectingFirst = this->selectingFirst == true ? false : true;
}

void CS_Selector::throwCommand() {
	cordScr dest = calculateSelectorCordOnControlled();
	Command_c* command_c = NULL;
	switch (this->operation) {
	case SELECTOR_ATTACK:
		 command_c = new Command_c(string("attack " + to_string(dest.x) + " " + to_string(dest.y)));
		break;
	case SELECTOR_MOVE:
		command_c = new Command_c(string("move to " + to_string(dest.x) + " " + to_string(dest.y)));
		break;
	}

	//	command_c->printCommand();
	if (!command_c) {
		return;
	}
	defaultConComCon->throwCommand(command_c);
	delete command_c;
}

//directions: 1 - up , 2 - down, 3 - left , 4 - right 
void CS_Selector::move(int direction) {
	cordScr newCords = this->cords;
	switch (direction) {
	case 1:
		newCords.y -= 1;
		break;
	case 2:
		newCords.y += 1;
		break;
	case 3:
		newCords.x -= 1;
		break;
	case 4:
		newCords.x += 1;
		break;
	}
	if (parentScreen) {
		if (cordScr(0, 0) <= newCords && newCords < cordScr(parentScreen->width, parentScreen->heigth)) {
			this->cords = newCords;
		}
	}
}

// up 72, down 80, left 75, rigth 77;
// alt up 152, alt down 160, alt left 155, alt rigth 157
//esc 27, enter 13, space 32,
//a 97, m 109, s 115, tab 9
void CS_Selector::operateKey(int keyid) {
	//cout << "key = " << keyid << endl;
	switch (keyid) {
	case 72: // arrow up
		this->move(1);
		break;
	case 80: // arrow down
		this->move(2);
		break;
	case 75: // arrow left
		this->move(3);
		break;
	case 77: // arrow right
		this->move(4);
		break;
	case 152: // alt arrow up
		//cout << "alt arrow up\n";
		if (this->controlledScreen) {
			controlledScreen->move(2);
		}
		break;
	case 160: // alt arrow down
		//cout << "alt arrow down\n";
		if (this->controlledScreen) {
			controlledScreen->move(1);
		}
		break;
	case 155: // alt arrow left
		//cout << "alt arrow left\n";
		if (this->controlledScreen) {
			controlledScreen->move(4);
		}
		break;
	case 157: // alt arrow rigth
		//cout << "alt arrow right\n";
		if (this->controlledScreen) {
			controlledScreen->move(3);
		}
		break;
	case 32: // space
		this->select();
		break;
	case 27: // esc
		this->selectingFirst = true;
		break;
	case 13: // enter
		this->throwCommand();
		break;
	case 97: // a
		this->operation = SELECTOR_ATTACK;
		cout << "attack" << endl;
		break;
	case 109: // m
		this->operation = SELECTOR_MOVE;
		cout << "move" << endl;
		break;
	}
}


void CS_Selector::catchEvent(Command_c* command, bool showHelp) {
	this->operateEvent(command, showHelp);
}

void CS_Selector::fillEventPatterns() {
	const EventPattern keyPressIdPattern(
		"key pressed id input_number CCC id input_number",
		"keyPressIdPattern",
		"key pressed id [int:keyid] CCC id [int:ConsoleCommandControllerId]",
		CS_Selector::keyPressIdCommand);
	this->eventPatterns.push_back(keyPressIdPattern);
}


//EV_CScreen EVENTS

// key pressed id [int:keyid] CCC id [int:ConsoleCommandControllerId]
void CS_Selector::keyPressIdCommand(Command_c * command, Eventable * oParent) {
	CS_Selector* parent = dynamic_cast<CS_Selector*>(oParent);
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
	if (input_cccid == parent->ConComConId) {
		parent->operateKey(input_keyid);
	}
}

