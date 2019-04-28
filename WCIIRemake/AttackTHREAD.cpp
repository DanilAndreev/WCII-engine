#include "pch.h"
#include "AttackTHREAD.h"

const time_t DEFAULTUNITSLEEP = 1000;

AttackTHREAD::AttackTHREAD(Obj* parent) {
	this->parent = parent;
}


AttackTHREAD::~AttackTHREAD() {
}

void AttackTHREAD::threadFunction() {
	LiveUnit* LUParent = (LiveUnit*)parent;
	time_t temp = clock() - LUParent->getLastAttackTime();
	if (temp < LUParent->getCooldown()) { // checking if after recreating thread cooldown weren't finished
		time_t deleteMe = clock();
		Sleep(temp);
	}
	while (isRunning) {
		if (!(LUParent->moveNoAttack) && LUParent->attack()) {
			Sleep(LUParent->getCooldown());
		}
		else {
			if (LUParent->getCord() != *(LUParent->getMoveDest())) {
				LUParent->goTo(LUParent->getMoveDest());
				//Sleep(1000);  //it is a stop in the goTo()
			}
			else {
				if (LUParent->moveNoAttack) {
					LUParent->moveNoAttack = false;
				}
				Sleep(DEFAULTUNITSLEEP);
			}
		}



	}
	this->isRunning = false;
}
