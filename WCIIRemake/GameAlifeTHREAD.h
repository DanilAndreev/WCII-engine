#pragma once
#include "Threadable.h"

const int SKIP_TIMEOUT = 500;


class GameAlifeTHREAD : public Threadable {
protected:
	Obj* parent;
public:
	GameAlifeTHREAD(Obj* parent);
	~GameAlifeTHREAD();
	HANDLE getThreadHandle();
protected:
	virtual void threadFunction();
};

