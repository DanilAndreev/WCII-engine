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
	cout << "GameAlifeTHREAD start" << endl;

	GameMaster* gmparent = (GameMaster*)parent;
	while (/*gmparent->gameAlifeThreadIsRunning && */this->isRunning) {
		Sleep(SKIP_TIMEOUT);
	}
	cout << "GameAlifeTHREAD stopping" << endl;
}
