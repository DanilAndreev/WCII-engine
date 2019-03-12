#pragma once
#include "pch.h"
#include "Obj.h"
#include "Threadable.h"
#include "Command_c.h"
#include <queue>
#include "EventHndlrTHREAD.h"

class Controller : public Obj {
private:
	Console* console;
	Field* field;
	MScreen* screen;
	DynArr* members;
	queue <Command_c> eventQueue;
//	bool EventHandlerRunning;

	bool dataWriting;
	ThreadId eventHandlerDescriptor;
public:
	Controller(Field* ifield, MScreen* screen, Console* ioconsole);
	~Controller();
	Command_c getEventFromQueue(); // Pop the event from processing queue
	void addEventToQueue(Command_c command); // Add the event to processing queue
	bool EventQueueIsEmpty();
	DynArr* getMembers();
	ThreadId getEventHandlerDescriptor();
	virtual void operateEvent(Command_c command); // Process phe incoming event
private:
//	void throwCommand(Command_c command);
	//void EventHandler();
	//virtual void threadFunction();

//CONTROLLER COMMANDS(EVENTS)
protected:
	bool exitGame(Command_c command);

};

