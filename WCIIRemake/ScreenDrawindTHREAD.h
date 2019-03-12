#pragma once
#include "Threadable.h"
class ScreenDrawindTHREAD : public Threadable {
protected:
	Obj* parent;
public:
	ScreenDrawindTHREAD(Obj* parent);
	~ScreenDrawindTHREAD();
protected:
	virtual void threadFunction();
};

