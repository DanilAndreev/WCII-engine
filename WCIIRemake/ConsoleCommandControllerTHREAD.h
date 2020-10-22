#pragma once
#include "Threadable.h"
#include "ConsoleCommandController.h"
class ConsoleCommandControllerTHREAD : public Threadable {
protected:
	Obj* parent;
public:
	ConsoleCommandControllerTHREAD(Obj* parent);
	~ConsoleCommandControllerTHREAD();
protected:
	virtual void threadFunction();
};

