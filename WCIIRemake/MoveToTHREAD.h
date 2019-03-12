#pragma once
#include "Threadable.h"
class MoveToTHREAD : public Threadable {
protected:
	Obj* parent;
public:
	MoveToTHREAD(Obj* parent);
	~MoveToTHREAD();
protected:
	virtual void threadFunction();
};

