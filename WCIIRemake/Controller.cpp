#include "pch.h"
#include "Controller.h"

extern Console* defaultConsole;

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
	EventHandlerRunning = false;
}


Controller::~Controller() {
}



void Controller::addEventToQueue(Command_c command) {
	eventQueue.push(command);
}


void Controller::throwCommand(Command_c command) {

//	command.printCommand();

	for (int i = 0; i < members->count(); i++) {
		members->get(i)->operateEvent(command);
	}
}



void Controller::EventHandler() {
	cout << "HandleEvent" << endl;
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

void Controller::operateEvent(Command_c command) {
	if (command == "exitgame") {
		exitGame(command);
	}
}

void Controller::threadFunction() {
	EventHandler();
}

//CONTROLLER COMMANDS(EVENTS)

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
