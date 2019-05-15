#include "pch.h"
#include "ConsoleCommandHandlerTHREAD.h"




void ConsoleCommandHandlerTHREAD::threadFunction() {
	ConsoleCommandController* cccparent = (ConsoleCommandController*)parent;
	while (isRunning) {
		cccparent->handleCommand(isRunning);
	}
}

ConsoleCommandHandlerTHREAD::~ConsoleCommandHandlerTHREAD() {
}
