#include "pch.h"
#include "ScreenDrawindTHREAD.h"


ScreenDrawindTHREAD::ScreenDrawindTHREAD(Obj* parent) {
	this->parent = parent;
}


ScreenDrawindTHREAD::~ScreenDrawindTHREAD() {

}

void ScreenDrawindTHREAD::threadFunction() {
//	cout << "ScreenDrawindTHREAD start" << endl;
	EV_CScreen_FPS* ScrParent = dynamic_cast<EV_CScreen_FPS*>(parent);
	if (!ScrParent) {
		return;
	}
	while (isRunning) {
		ScrParent->render();
		Sleep(1000/ScrParent->getFrameRate());
	}
	isRunning = false;
//	cout << "ScreenDrawindTHREAD stopping" << endl;
}


