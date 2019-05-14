#include "pch.h"
#include "ConsoleCommandControllerTHREAD.h"


ConsoleCommandControllerTHREAD::ConsoleCommandControllerTHREAD(Obj* parent) {
	this->parent = parent;
}


ConsoleCommandControllerTHREAD::~ConsoleCommandControllerTHREAD() {
}

void ConsoleCommandControllerTHREAD::threadFunction() {
//	cout << "ConsoleCommandControllerTHREAD start" << endl;

	ConsoleCommandController* ConParent = (ConsoleCommandController*)parent;
	ConParent->console->message("Command: ");
	while (isRunning) {
		if (!ConParent->isPaused) {
			Command_c command = ConParent->getCommand();
			if (command.args[0].first != "empty") {
				ConParent->throwCommand(&command);
			}
			Sleep(10);
		}
		else {
			Sleep(100);
		}
	}
	isRunning = false;
//	cout << "ConsoleCommandControllerTHREAD stopping" << endl;
}
