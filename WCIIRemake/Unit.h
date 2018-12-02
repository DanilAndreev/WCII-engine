#pragma once

#include "pch.h"
#include "Screenable.h"


class Unit : public Screenable {
protected:
	Field* field;
	char value;//for debug
	int type;
public:

//	Unit(Unit** field);
	Unit(cordScr cords, char value,int type, Field* field);
	Unit(cordScr cords, Field* field) : Unit(cords, 'd', 1, field) {}
	Unit(cordScr cords, int type, Field* field) : Unit(cords, 'd', type, field) {}
	Unit(char value, int type, Field* field) : Unit(cordScr(0, 0), value, type, field) {}
	Unit(char value, Field* field) : Unit(cordScr(0, 0), value, 1, field) {}
	Unit() : Unit(cordScr(0, 0), NULL) {}



	char getValue();
	virtual ~Unit();
	int getType();
	//1-up,2-down,3-rigth,4-left
	int move(int direction);
	virtual void render();
private:
	int findPath(cordScr destC);
};

