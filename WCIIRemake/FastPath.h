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
private:
	bool checkCords(cordScr cords);
	void createSolveQueue();
	int lineLength(cordScr cord1, cordScr cord2);
	inline int sqr(int input);
	int determineDirection(cordScr cords);
};


