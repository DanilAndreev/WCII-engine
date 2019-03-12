#include "pch.h"
#include "ScreenDrawindTHREAD.h"


ScreenDrawindTHREAD::ScreenDrawindTHREAD(Obj* parent) {
	this->parent = parent;
}


ScreenDrawindTHREAD::~ScreenDrawindTHREAD() {

}

void ScreenDrawindTHREAD::threadFunction() {
	MScreen* ScrParent = (MScreen*)parent;
	while (isRunning) {
		ScrParent->render();
		Sleep(100);
	}
	isRunning = false;
}


