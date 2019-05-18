#pragma once
#include "pch.h"
#include "Obj.h"
#include "Threadable.h"
#include "Command_c.h"
#include <queue>
#include "EventHndlrTHREAD.h"
#include "GameMaster.h"
#include "CommandPatterns.h"
#include "Eventable.h"

class Controller :public Obj {
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
	bool eventHandlerIsPaused;
public:	
	Controller(Field* ifield, MScreen* screen, Console* ioconsole, GameMaster* gameMaster);
	~Controller();
	bool setField(Field* field);
	bool setScreen(MScreen* screen);
	bool setConsole(Console* console);
	bool setup(Console* console, MScreen* screen, Field* field, GameMaster* gameMaster);
	Command_c getEventFromQueue(); // Pop the event from processing queue
	void addEventToQueue(Command_c command); // Add the event to processing queue
	bool EventQueueIsEmpty();
	void pauseEventHandler();
	void unpauseEventHandler();
	void clearMembers();
	DynArr* getMembers();
	bool addEventableMember(Obj * target, string description);
	bool addEventableMember(Obj* target);
	ThreadId getEventHandlerDescriptor();
	Command_c* throwCommand(Command_c* command);
	virtual void catchEvent(Command_c* command, bool showHelp);
protected:
	virtual void fillEventPatterns();
public: //CONTROLLER EVENTS
	static void exitGameCommand(Command_c* command, Eventable* oParent);
	static void stopThreadsCommand(Command_c* command, Eventable* oParent);
};

// exitgame
// stop threads {flags}

