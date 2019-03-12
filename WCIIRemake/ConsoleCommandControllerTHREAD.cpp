#include "pch.h"
#include "ConsoleCommandControllerTHREAD.h"


ConsoleCommandControllerTHREAD::ConsoleCommandControllerTHREAD(Obj* parent) {
	this->parent = parent;
}


ConsoleCommandControllerTHREAD::~ConsoleCommandControllerTHREAD() {
}

void ConsoleCommandControllerTHREAD::threadFunction() {
	ConsoleCommandController* ConParent = (ConsoleCommandController*)parent;
	ConParent->console->message("Command: ");
	while (isRunning) {
		Command_c command = ConParent->getCommand();
		if (command.args[0].first != "empty") {
			ConParent->throwCommand(command);
		}
		Sleep(10);
	}
	isRunning = false;
}
