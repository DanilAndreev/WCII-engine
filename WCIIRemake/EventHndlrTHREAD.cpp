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
			Command_c command = ((Controller*)parent)->getEventFromQueue();
			if (command.args[0].first != "empty") {
				throwCommand(command);
			}
		}
	}
	isRunning = false;
}

void EventHndlrTHREAD::throwCommand(Command_c command) {
	//	command.printCommand();
	for (int i = 0; i < ((Controller*)parent)->getMembers()->count(); i++) {
		((Controller*)parent)->getMembers()->get(i)->operateEvent(command);
	}
}


HANDLE EventHndlrTHREAD::getThreadHandle() {
	return this->threadHandle;
}
