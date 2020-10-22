#pragma once
#include "Threadable.h"
#include "EV_CScreen_FPS.h"

class ScreenDrawindTHREAD : public Threadable {
protected:
	Obj* parent;
public:
	ScreenDrawindTHREAD(Obj* parent);
	~ScreenDrawindTHREAD();
protected:
	virtual void threadFunction();
};

