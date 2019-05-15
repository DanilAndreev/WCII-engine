#pragma once
#include "Threadable.h"
class ConsoleCommandHandlerTHREAD : public Threadable {
protected:
	Obj* parent;
public:
	ConsoleCommandHandlerTHREAD(Obj* parent) : parent(parent) {}
	virtual ~ConsoleCommandHandlerTHREAD();
protected:
	virtual void threadFunction();
};

