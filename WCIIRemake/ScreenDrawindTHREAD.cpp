#include "pch.h"
#include "ScreenDrawindTHREAD.h"


ScreenDrawindTHREAD::ScreenDrawindTHREAD(Obj* parent) {
	this->parent = parent;
}


ScreenDrawindTHREAD::~ScreenDrawindTHREAD() {

}

void ScreenDrawindTHREAD::threadFunction() {
	EV_CScreen_FPS* ScrParent = dynamic_cast<EV_CScreen_FPS*>(parent);
	if (!ScrParent) {
		return;
	}
	while (isRunning) {
		time_t begin = clock();
		ScrParent->render(*ScrParent->getTeam());
		time_t end = clock();

		time_t rateSleep = 1000 / ScrParent->getFrameRate();

		time_t targetSleep = rateSleep - (end - begin);
		if (targetSleep < 0) {
			targetSleep = 0;
		}
		Sleep(targetSleep);
	}
	isRunning = false;
}


