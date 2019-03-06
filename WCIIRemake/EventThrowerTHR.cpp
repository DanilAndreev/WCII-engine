#include "pch.h"
#include "EventThrowerTHR.h"


EventThrowerTHR::EventThrowerTHR(Controller* parent) {
	this->parent = parent;
	Threadable::Threadable(); // starting thread
}


EventThrowerTHR::~EventThrowerTHR() {
	Threadable::Threadable();
}

void EventThrowerTHR::threadFunction() {
	while (isRunning) {
		if (parent->EventQueueIsEmpty()) {
			Sleep(10);
		}
		else {
			Command_c command = parent->getEventFromQueue();
			if (command.args[0].first != "empty") {
				throwCommand(command);
			}
		}
	}
}

void EventThrowerTHR::throwCommand(Command_c command) {
	//	command.printCommand();
	for (int i = 0; i < parent->getMembers()->count(); i++) {
		parent->getMembers()->get(i)->operateEvent(command);
	}
}

HANDLE EventThrowerTHR::getThreadHandle()
{
	return this->threadHandle;
}
