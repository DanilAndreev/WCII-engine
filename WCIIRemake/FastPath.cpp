#include "pch.h"
#include "FastPath.h"


FastPath::FastPath(Field* field, Unit* unit) {
	this->field = field;
	this->unit = unit;
	solveQueue.clear();
}


FastPath::~FastPath() {
	solveQueue.clear();
}



int FastPath::solveDirection(cordScr dest) {
	this->dest = dest;
	if (dest == unit->getCords()) {
		return -1;
	}
	solveQueue.clear();
	createSolveQueue();

	if (solveQueue.empty()) {
		solveQueue.clear();
		return 0;
	}

	cordScr minCords = solveQueue[0];
	float firstLen = minCords.lineLength(dest, minCords);
	float minLen = firstLen;
	for (int i = 1; i < solveQueue.size(); i++) {
		int curLen = minCords.lineLength(dest, solveQueue[i]);
		if (curLen < minLen) {
			minLen = curLen;
			minCords = solveQueue[i];
		}
	}
	solveQueue.clear();
	if (minLen == firstLen) {
		return 0;
	}
	if (minLen >= unit->getCords().lineLength(unit->getCords(), dest)) {
		return 0;
	}
	return determineDirection(minCords);
}

bool FastPath::checkCords(cordScr cords) {
	if (!(cords.x >= 0 && cords.x < field->getWidth() && cords.y >= 0 && cords.y < field->getHeigth())) {
		return false;
	}

	for (int i = 0; i < field->getMembers()->count(); i++) {
		Unit* unitC = (Unit*)(field->getMembers()->get(i));
		if (unitC->getType() == this->unit->getType() && unitC->getCords() == cords) {
			return false;
		}
	}
	return true;
}

void FastPath::createSolveQueue() {
	cordScr checkingCords;
	// UP
	checkingCords = cordScr(unit->getCords().x, unit->getCords().y - 1);
	if (checkCords(checkingCords)) {
		solveQueue.push_back(checkingCords);
	}
	// DOWN
	checkingCords = cordScr(unit->getCords().x, unit->getCords().y + 1);
	if (checkCords(checkingCords)) {
		solveQueue.push_back(checkingCords);
	}
	// RIGHT
	checkingCords = cordScr(unit->getCords().x + 1, unit->getCords().y);
	if (checkCords(checkingCords)) {
		solveQueue.push_back(checkingCords);
	}
	// LEFT
	checkingCords = cordScr(unit->getCords().x - 1, unit->getCords().y);
	if (checkCords(checkingCords)) {
		solveQueue.push_back(checkingCords);
	}
	// UP RIGHT
	checkingCords = cordScr(unit->getCords().x + 1, unit->getCords().y - 1);
	if (checkCords(checkingCords)) {
		solveQueue.push_back(checkingCords);
	}
	// UP LEFT
	checkingCords = cordScr(unit->getCords().x - 1, unit->getCords().y - 1);
	if (checkCords(checkingCords)) {
		solveQueue.push_back(checkingCords);
	}
	// DOWN RIGHT
	checkingCords = cordScr(unit->getCords().x + 1, unit->getCords().y + 1);
	if (checkCords(checkingCords)) {
		solveQueue.push_back(checkingCords);
	}
	// DOWN LEFT
	checkingCords = cordScr(unit->getCords().x - 1, unit->getCords().y + 1);
	if (checkCords(checkingCords)) {
		solveQueue.push_back(checkingCords);
	}
}



int FastPath::determineDirection(cordScr cords) {
	cordScr uCords = unit->getCords();
	// UP
	if (cords.x == uCords.x && cords.y < uCords.y) {
		return 1;
	}
	// DOWN
	if (cords.x == uCords.x && cords.y > uCords.y) {
		return 2;
	}
	// RIGHT
	if (cords.x > uCords.x && cords.y == uCords.y) {
		return 3;
	}
	// LEFT
	if (cords.x < uCords.x && cords.y == uCords.y) {
		return 4;
	}
	// UP RIGHT
	if (cords.x > uCords.x && cords.y < uCords.y) {
		return 5;
	}
	// UP LEFT
	if (cords.x < uCords.x && cords.y < uCords.y) {
		return 6;
	}
	// DOWN RIGHT
	if (cords.x > uCords.x && cords.y > uCords.y) {
		return 7;
	}
	// DWON LEFT
	if (cords.x < uCords.x && cords.y > uCords.y) {
		return 8;
	}

	return 0;
}


