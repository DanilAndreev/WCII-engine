#pragma once
#include "Threadable.h"
#include "Obj.h"

class EventHndlrTHREAD : public Threadable {
protected:
	Obj* parent;
public:
	EventHndlrTHREAD(Obj* parent);
	~EventHndlrTHREAD();
	HANDLE getThreadHandle();
protected:
	virtual void threadFunction();
};

