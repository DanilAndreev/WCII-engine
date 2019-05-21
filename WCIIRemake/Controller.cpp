#include "pch.h"
#include "Controller.h"

extern Console* defaultConsole;
extern ThreadDescriptor* gameThreads;
extern ConsoleCommandController* defaultConComCon;


Controller::Controller(Field* ifield, MScreen* iscreen, Console* ioconsole, GameMaster* igameMaster) {
	this->fillEventPatterns();
	setDescription("Controller");
	this->members = new DynArr();
	eventHandlerIsPaused = false;
	this->eventHandlerDescriptor = 0;
	setup(ioconsole, iscreen, ifield, igameMaster);

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
	delete members;
}

bool Controller::setField(Field* field) {
	if (field) {
		this->field = field;
		this->members->add(field);
		return true;
	}
	return false;
}

bool Controller::setScreen(MScreen* ascreen) {
	if (ascreen) {
		this->screen = ascreen;
		this->members->add(ascreen);
		return true;
	}
	return false;
}

bool Controller::setConsole(Console* ioconsole) {
	if (ioconsole != NULL) {
		this->console = ioconsole;
	} 
	else {
		this->console = defaultConsole;
	}
	if (!console) throw new exception("error");
	this->members->add(console);
	return true;
}

bool Controller::setup(Console* console, MScreen* screen, Field* field, GameMaster* gameMaster) {
	this->clearMembers();
//	this->setField(field);
	this->setConsole(console);
	this->setScreen(screen);
	this->members->add(gameMaster);
//	this->members->add(console);
//	this->members->add(screen);
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
//	cout << "Paused event handler" << endl;
	this->eventHandlerIsPaused = true;
}

void Controller::unpauseEventHandler() {
//	cout << "Unpaused event handler" << endl;
	this->eventHandlerIsPaused = false;
}

void Controller::clearMembers() {
	this->members->clear();
	field = NULL;
	screen = NULL;
	console = NULL;
}

DynArr * Controller::getMembers() {
	return this->members;
}

bool Controller::addEventableMember(Obj* target, string description) {
	return members->add(target);
}

bool Controller::addEventableMember(Obj* target) {
	return addEventableMember(target, "no description");
}



ThreadId Controller::getEventHandlerDescriptor() {
	return eventHandlerDescriptor;
}


Command_c* Controller::throwCommand(Command_c* command) {
	//	command.printCommand();
//	Command_c* eventCommand = new Command_c();
//	*eventCommand = command;

/*
	cout << "Controller members: ";
	for (int i = 0; i < members->count(); i++) {
		Obj* o = members->get(i);
		cout << o->getDescription() << " ";
	}
	cout << endl;
*/
	if (!this) {
		return command;
	}
	if (!this->eventHandlerIsPaused) {
		/*
				defaultConComCon->operateEvent(command);
		for (int i = 0; i < members->count(); i++) {
			Obj* object = members->get(i);
			if (object) {
				object->catchEvent(command, false);
			}
		}
*/
		this->catchEvent(command, false);
	}
	else {
//		cout << "cannot operate event: EventHandlerPaused" << endl;
	}
	return command;
}

void Controller::catchEvent(Command_c* command, bool showHelp) {
	defaultConComCon->operateEvent(command, showHelp);
	for (int i = 0; i < members->count(); i++) {
		members->get(i)->catchEvent(command, showHelp);
	}
	this->operateEvent(command, showHelp);
}


void Controller::fillEventPatterns() {
	const EventPattern exitGamePattern(
		"exitgame",
		"exitGamePattern",
		"exitgame",
		Controller::exitGameCommand);
	const EventPattern stopThreadsPattern(
		"stop threads",
		"stopThreadsPattern",
		"stop threads {flags}",
		Controller::stopThreadsCommand);

	this->eventPatterns.push_back(exitGamePattern);
	this->eventPatterns.push_back(stopThreadsPattern);
}


//CONTROLLER EVENTS

// exitgame
void Controller::exitGameCommand(Command_c* command, Eventable* oParent) {
	Controller* parent = dynamic_cast<Controller*>(oParent);
	if (!parent) {
		return;
	}
	gameThreads->stopThread(parent->eventHandlerDescriptor);
}

// stop threads {flags}
void Controller::stopThreadsCommand(Command_c* command, Eventable* oParent) {
	Controller* parent = dynamic_cast<Controller*>(oParent);
	if (!parent) {
		return;
	}
	if (!command->checkFlag("-eh")) {
		gameThreads->stopThread(parent->eventHandlerDescriptor);
	}
	if (command->checkFlag("-wait")) {
		for (int i = 0; i < command->data.size(); i++) {
			eventReturnDataHandle* temp = dynamic_cast<eventReturnDataHandle*>(command->data[i]);
			if (temp) {
				WaitForSingleObject(temp->handle, INFINITE);
			}
		}
	}
}


