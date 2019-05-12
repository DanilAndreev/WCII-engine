#include "pch.h"
#include "Controller.h"

extern Console* defaultConsole;
extern ThreadDescriptor* gameThreads;
extern ConsoleCommandController* defaultConComCon;


Controller::Controller(Field* ifield, MScreen* screen, Console* ioconsole, GameMaster* gameMaster) {
	eventHandlerIsPaused = false;
	this->eventHandlerDescriptor = 0;
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
	members->add(gameMaster);
	//members->add(this);  //CAUTION:: Controller is a member of itself!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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
		this->members->add(field);
		return true;
	}
	return false;
}

bool Controller::setScreen(MScreen* screen) {
	if (screen) {
		this->screen = screen;
		this->members->add(field);
		return true;
	}
	return false;
}

bool Controller::setConsole(Console* console) {
	if (console) {
		this->console = console;
		this->members->add(console);
		return true;
	}
	return false;
}

bool Controller::setup(Console* console, MScreen* screen, Field* field, GameMaster* gameMaster) {
	this->clearMembers();
	this->setField(field);
	this->setConsole(console);
	this->setScreen(screen);
	this->members->add(gameMaster);
	return true;
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

void Controller::pauseEventHandler() {
	cout << "Paused event handler" << endl;
	this->eventHandlerIsPaused = true;
}

void Controller::unpauseEventHandler() {
	cout << "Unpaused event handler" << endl;
	this->eventHandlerIsPaused = false;
}

void Controller::clearMembers() {
	this->members->clear();
}

DynArr * Controller::getMembers() {
	return this->members;
}

bool Controller::addEventableMember(Obj* target) {
	return members->add(target);
}

ThreadId Controller::getEventHandlerDescriptor()
{
	return eventHandlerDescriptor;
}



Command_c* Controller::throwCommand(Command_c* command) {
	//	command.printCommand();
//	Command_c* eventCommand = new Command_c();
//	*eventCommand = command;
	if (!this->eventHandlerIsPaused) {
		defaultConComCon->operateEvent(command);
		for (int i = 0; i < members->count(); i++) {
			Obj* object = members->get(i);
			if (object) {
				object->operateEvent(command);
			}
		}
		this->operateEvent(command);
	}
	else {
		cout << "cannot operate event: EventHandlerPaused" << endl;
	}
	return command;
}


void Controller::operateEvent(Command_c* command) {
	if (*command == "exitgame") {
		exitGame(command);
	}
	if (*command == "stop") {
		stopEvent(command);
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


bool Controller::stopEvent(Command_c* command) {
	if (command->args.size() >= 2) {
		if (command->args[1].first == "threads" && command->args[1].second == "command") {
			if (!command->checkFlag("-eh")) {
				gameThreads->stopThreadNoWait(this->eventHandlerDescriptor);
				cout << "stpping eventHandler thread by event" << endl;

			}
			return true;
		}
	}
	return false;
}
