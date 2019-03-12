#include "pch.h"
#include "Controller.h"

extern Console* defaultConsole;
extern ThreadDescriptor* gameThreads;

Controller::Controller(Field* ifield, MScreen* screen, Console* ioconsole) {
	if (ioconsole != NULL) {
		this->console = ioconsole;
	}
	else {
		this->console = defaultConsole;
	}
	this->screen = screen;
	this->field = ifield;
	this->members = new DynArr();
	members->add(field);
	members->add(screen);
	members->add(this);  //CAUTION:: Controller is a member of itself!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	dataWriting = false;

	EventHndlrTHREAD* eventHandler = new EventHndlrTHREAD(this);

	
	//gameThreads->add(eventHandler);
	if (eventHandler) {
		this->eventHandlerDescriptor = eventHandler->getDescriptor();
	}
	else {
		cout << "Error allocating memory" << endl;
	}
	eventHandler->startThread();
}


Controller::~Controller() {
}

Command_c Controller::getEventFromQueue() {
	while (dataWriting) {
		Sleep(10);
	}
	Command_c command;
	dataWriting = true;
	command = eventQueue.front();
	eventQueue.pop();
	dataWriting = false;
	return command;
}



void Controller::addEventToQueue(Command_c command) {
	while (dataWriting) {
		Sleep(10);
	}
	dataWriting = true;
	eventQueue.push(command);
	dataWriting = false;
}

bool Controller::EventQueueIsEmpty() {
	if (eventQueue.empty()) {
		return true;
	}
	return false;
}

DynArr * Controller::getMembers() {
	return this->members;
}

ThreadId Controller::getEventHandlerDescriptor()
{
	return eventHandlerDescriptor;
}

/*
void Controller::throwCommand(Command_c command) {

//	command.printCommand();

	for (int i = 0; i < members->count(); i++) {
		members->get(i)->operateEvent(command);
	}
}
*/

/*
void Controller::EventHandler() {
	this->EventHandlerRunning = true;
	while (EventHandlerRunning) {
		if (eventQueue.empty()) {
			Sleep(10);
		}
		else {
			Command_c command = eventQueue.front();
			eventQueue.pop();
			if (command.args[0].first != "empty") {
				throwCommand(command);
			}
		}
	}
	this->EventHandlerRunning = false;
}

*/

void Controller::operateEvent(Command_c command) {
	if (command == "exitgame") {
//		exitGame(command);
	}
}

/*
void Controller::threadFunction() {
	EventHandler();
}
*/

//CONTROLLER COMMANDS(EVENTS)


/*
bool Controller::exitGame(Command_c command) {
	if (command.args.size() == 1) {
		if (this->EventHandlerRunning) {
			EventHandlerRunning = false;
			console->message("Stopping EventHandler");
			return true;
		}
	}
	return false;
}
*/