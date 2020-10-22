#include "pch.h"
#include "EV_CScreen.h"


EV_CScreen::EV_CScreen(cordScr icords, int iwidth, int iheigth, CScreenPixel dafaultFill, int ilayer) : CScreen(icords, iwidth, iheigth, dafaultFill, ilayer) {
	this->fillEventPatterns();
}


EV_CScreen::~EV_CScreen() {
}

void EV_CScreen::catchEvent(Command_c* command, bool showHelp) {
	for (int i = 0; i < members.size(); i++) {
		Eventable* temp = dynamic_cast<Eventable*>(members[i]);
		if (temp) {
			temp->catchEvent(command, showHelp);
		}
	}
	this->operateEvent(command, showHelp);
}


void EV_CScreen::fillEventPatterns() {
	const EventPattern renderScreenIdPattern(
		"render screen id input_number",
		"renderScreenIdPattern",
		"render screen id [int:id]",
		EV_CScreen::renderScreenIdCommand);
	const EventPattern renderScreenPattern(
		"render screen",
		"renderScreenPattern",
		"render screen {flags}",
		EV_CScreen::renderScreenCommand);
	const EventPattern drawScreenIdPattern(
		"draw screen id input_number",
		"drawScreenIdPattern",
		"draw screen id [int:id]",
		EV_CScreen::drawScreenIdCommand);
	this->eventPatterns.push_back(renderScreenIdPattern);
	this->eventPatterns.push_back(renderScreenPattern);
	this->eventPatterns.push_back(drawScreenIdPattern);
}

//EV_CScreen EVENTS


// render screen id [int:id]
void EV_CScreen::renderScreenIdCommand(Command_c* command, Eventable* oParent) {
	EV_CScreen* parent = dynamic_cast<EV_CScreen*>(oParent);
	if (!parent) {
		return;
	}
	ID input_id = 0;
	try {
		input_id = stoull(command->args[3].first);
	}
	catch (...) {
		return;
	}
	if (input_id == parent->id) {
		parent->render(0);
	}
}

void EV_CScreen::renderScreenCommand(Command_c* command, Eventable* oParent) {
	EV_CScreen* parent = dynamic_cast<EV_CScreen*>(oParent);
	if (!parent) {
		return;
	}
	if (command->checkFlag("-all")) {
		parent->render(1);
	}
}

// draw screen id [int:id]
void EV_CScreen::drawScreenIdCommand(Command_c* command, Eventable* oParent) {
	EV_CScreen* parent = dynamic_cast<EV_CScreen*>(oParent);
	if (!parent) {
		return;
	}
	ID input_id = 0;
	try {
		input_id = stoull(command->args[3].first);
	}
	catch (...) {
		return;
	}
	if (input_id == parent->id) {
		parent->draw();
	}
}

