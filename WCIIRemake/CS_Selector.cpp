#include "pch.h"
#include "CS_Selector.h"


CS_Selector::CS_Selector(ID CccID) : Placable(cordScr(3,3), 1000) {
	this->fillEventPatterns();
	this->symbol = CScreenPixel('+', COLOR_BLUE);
	this->ConComConId = CccID;
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

// up 72, down 80, left 75, rigth 77;
void CS_Selector::operateKey(int keyid) {
	switch (keyid) {
	case 72:
		this->cords.y -= 1;
		break;
	case 80:
		this->cords.y += 1;
		break;
	case 75:
		this->cords.x -= 1;
		break;
	case 77:
		this->cords.x += 1;
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

