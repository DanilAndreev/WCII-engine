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

bool Controller::setField(Field* field) {
	if (field) {
		this->field = field;
		return true;
	}
	return false;
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



Command_c* Controller::throwCommand(Command_c* command) {
	//	command.printCommand();
//	Command_c* eventCommand = new Command_c();
//	*eventCommand = command;
	for (int i = 0; i < members->count(); i++) {
		Obj* object = members->get(i);
		if (object) {
			object->operateEvent(command);
		}
	}
	return command;
}


void Controller::operateEvent(Command_c* command) {
	if (*command == "exitgame") {
		exitGame(command);
	}
}

//CONTROLLER COMMANDS(EVENTS)



bool Controller::exitGame(Command_c* command) {
	if (command->args.size() == 1) {
		console->message("Stopping EventHandler");
		return gameThreads->stopThread(eventHandlerDescriptor);
	}
	return false;
}
