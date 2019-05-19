#include "pch.h"
#include "ScreenDrawindTHREAD.h"


ScreenDrawindTHREAD::ScreenDrawindTHREAD(Obj* parent) {
	this->parent = parent;
}


ScreenDrawindTHREAD::~ScreenDrawindTHREAD() {

}

void ScreenDrawindTHREAD::threadFunction() {
//	cout << "ScreenDrawindTHREAD start" << endl;
	MScreen* ScrParent = (MScreen*)parent;
	while (isRunning) {
		ScrParent->render(0);
		Sleep(100);
	}
	isRunning = false;
//	cout << "ScreenDrawindTHREAD stopping" << endl;
}


