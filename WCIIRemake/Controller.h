#pragma once
#include "pch.h"
#include "Obj.h"
#include "Threadable.h"
#include "Command_c.h"
#include <queue>


class Controller : public Obj, public Threadable {
private:
	Console* console;
	Field* field;
	MScreen* screen;
	DynArr* members;
	queue <Command_c> eventQueue;
	bool EventHandlerRunning;
public:
	Controller(Field* ifield, MScreen* screen, Console* ioconsole);
	~Controller();
	void addEventToQueue(Command_c command); // Add the event to processing queue
	virtual void operateEvent(Command_c command); // Process phe incoming event
private:
	void throwCommand(Command_c command);
	void EventHandler();
	virtual void threadFunction();

//CONTROLLER COMMANDS(EVENTS)
private:
	bool exitGame(Command_c command);

};

