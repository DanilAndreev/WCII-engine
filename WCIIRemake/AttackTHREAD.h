#pragma once
#include "Threadable.h"
class AttackTHREAD : public Threadable {
protected:
	Obj* parent;
public:
	AttackTHREAD(Obj* parent);
	~AttackTHREAD();
protected:
	virtual void threadFunction();
};

