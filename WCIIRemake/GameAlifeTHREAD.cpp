#include "pch.h"
#include "GameAlifeTHREAD.h"


GameAlifeTHREAD::GameAlifeTHREAD(Obj* parent) {
	this->parent = parent;
}


GameAlifeTHREAD::~GameAlifeTHREAD()
{
}

HANDLE GameAlifeTHREAD::getThreadHandle() {
	return this->threadHandle;
}

void GameAlifeTHREAD::threadFunction() {
	GameMaster* gmparent = (GameMaster*)parent;
	while (this->isRunning) {
		Sleep(SKIP_TIMEOUT);
	}
}
