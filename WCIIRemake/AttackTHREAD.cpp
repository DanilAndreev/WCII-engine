#include "pch.h"
#include "AttackTHREAD.h"


AttackTHREAD::AttackTHREAD(Obj* parent) {
	this->parent = parent;
}


AttackTHREAD::~AttackTHREAD() {
}

void AttackTHREAD::threadFunction() {
	LiveUnit* LUParent = (LiveUnit*)parent;
	while (isRunning) {
		if (LUParent->attack()) {
			Sleep(1000);// TODO: change to cooldown
		}
		else {
			Sleep(1000);
		}
	}
	this->isRunning = false;
}
