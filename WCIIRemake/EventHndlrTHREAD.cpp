#include "pch.h"
#include "EventHndlrTHREAD.h"


EventHndlrTHREAD::EventHndlrTHREAD(Obj* parent) {
	this->parent = parent;
}

EventHndlrTHREAD::~EventHndlrTHREAD() {
}

void EventHndlrTHREAD::threadFunction() {
	Controller* cparent = (Controller*)parent;
	while (isRunning) {
		if (!cparent->eventHandlerIsPaused) {
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
		else {
			Sleep(100);
		}
	}
	isRunning = false;
}

HANDLE EventHndlrTHREAD::getThreadHandle() {
	return this->threadHandle;
}
