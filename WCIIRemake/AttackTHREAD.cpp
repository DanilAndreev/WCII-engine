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
	if (isRunning && temp < LUParent->getCooldown()) { // checking if after recreating thread cooldown weren't finished
		time_t deleteMe = clock();
		Sleep((DWORD)temp);
	}
	while (isRunning) {
		if (isRunning && !(LUParent->moveNoAttack) && LUParent->attack(isRunning)) {
			Sleep((DWORD)LUParent->getCooldown());
		}
		else {
			if (isRunning && LUParent->getCords() != *(LUParent->getMoveDest())) {
				LUParent->goTo(LUParent->getMoveDest(), isRunning);
			}
			else {
				if (isRunning && LUParent->moveNoAttack) {
					LUParent->moveNoAttack = false;
				}
				Sleep(DEFAULTUNITSLEEP);
			}
		}
	}
	this->isRunning = false;
}
