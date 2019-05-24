#pragma once
#include "Unit.h"
#include "Field.h"
#include "Screenable.h"
#include <cmath>

class FastPath {
private:
	Field* field;
	Unit* unit;
	vector <cordScr> solveQueue;
	cordScr dest;
public:
	FastPath(Field* field, Unit* unit);
	virtual ~FastPath();
	int solveDirection(cordScr dest);
	int determineDirection(cordScr cords);
private:
	bool checkCords(cordScr cords);
	void createSolveQueue();
};


