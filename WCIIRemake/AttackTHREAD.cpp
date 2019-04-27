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
		if (!(LUParent->moveNoAttack) && LUParent->attack()) {
			Sleep(1000);// TODO: change to cooldown
		}
		else {
			if (LUParent->getCord() != *(LUParent->getMoveDest())) {
				LUParent->goTo(LUParent->getMoveDest());
				//Sleep(1000);  //it is an stop in the goTo()
			}
			else {
				if (LUParent->moveNoAttack) {
					LUParent->moveNoAttack = false;
				}
				Sleep(1000);
			}
		}



	}
	this->isRunning = false;
}
