#pragma once
#include "cordScr.h"


class Placable {
protected:
	cordScr cords;
	int layer;
public:
	Placable(cordScr icords, int ilayer) : cords(icords), layer(ilayer) {}
	Placable() : Placable(cordScr(0, 0), 1) {}
	virtual ~Placable();
	cordScr getCords();
	void setCords(cordScr newcords);
};

