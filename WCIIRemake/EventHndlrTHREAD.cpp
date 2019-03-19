#include "pch.h"
#include "EventHndlrTHREAD.h"


EventHndlrTHREAD::EventHndlrTHREAD(Obj* parent) {
	this->parent = parent;
}

EventHndlrTHREAD::~EventHndlrTHREAD() {
}

void EventHndlrTHREAD::threadFunction() {
	while (isRunning) {
		if (((Controller*)parent)->EventQueueIsEmpty()) {
			Sleep(10);
		}
		else {
			Command_c* command = new Command_c();
			*command = ((Controller*)parent)->getEventFromQueue();
			if (command->args[0].first != "empty") {
				((Controller*)parent)->throwCommand(command);
				delete command;
			}
		}
	}
	isRunning = false;
}

/*
void EventHndlrTHREAD::throwCommand(Command_c command) {
	//	command.printCommand();
	Command_c* eventCommand = new Command_c();
	*eventCommand = command;

	
	for (int i = 0; i < ((Controller*)parent)->getMembers()->count(); i++) {
		Obj* object = ((Controller*)parent)->getMembers()->get(i);
		if (object) {
			object->operateEvent(eventCommand);
		}
	}
	delete eventCommand;
}
*/

HANDLE EventHndlrTHREAD::getThreadHandle() {
	return this->threadHandle;
}
