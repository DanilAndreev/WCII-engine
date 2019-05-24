#include "pch.h"
#include "ConsoleCommandControllerTHREAD.h"

extern Controller* gameController;

ConsoleCommandControllerTHREAD::ConsoleCommandControllerTHREAD(Obj* parent) {
	this->parent = parent;
}


ConsoleCommandControllerTHREAD::~ConsoleCommandControllerTHREAD() {
}

void ConsoleCommandControllerTHREAD::threadFunction() {
	ConsoleCommandController* ConParent = (ConsoleCommandController*)parent;
	ConParent->console->message("Command: ");
	while (isRunning) {
		if (!ConParent->isPaused) {
			if (ConParent->commandInput) {
				Command_c command = ConParent->getCommand();
				if (command.args[0].first != "empty") {
					ConParent->throwCommand(&command);
				}
				Sleep(10);
			}
			else {
				KeyID keyID = ConParent->getKey();
				Command_c command(string("key pressed id ") + to_string(keyID) + " CCC id " + to_string(ConParent->getId()));
				gameController->addEventToQueue(command);
			}
		}
		else {
			Sleep(100);
		}
	}
	isRunning = false;
}
