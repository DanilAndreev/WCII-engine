#include "pch.h"
#include "MoveToTHREAD.h"


MoveToTHREAD::MoveToTHREAD(Obj* parent) {
	this->parent = parent;
}


MoveToTHREAD::~MoveToTHREAD() {
}

void MoveToTHREAD::threadFunction(){
	LiveUnit* LUParent = (LiveUnit*)parent;
	LUParent->goTo(LUParent->getMoveDest());
}

