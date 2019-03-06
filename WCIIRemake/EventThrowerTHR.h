#pragma once
#include "Threadable.h"



class EventThrowerTHR : public Threadable {
protected:
	Controller* parent;
public:
	EventThrowerTHR(Controller* parent);
	virtual ~EventThrowerTHR();
	virtual void threadFunction();
	void throwCommand(Command_c command);
	HANDLE getThreadHandle();
};

