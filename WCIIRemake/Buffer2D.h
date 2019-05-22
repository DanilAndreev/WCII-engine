#pragma once
#include "CScreenPixel.h"
#include "Placable.h"


class Buffer2D {
public:
	int width;
	int heigth;
	CScreenPixel** Buff;
public:
	Buffer2D(int iwidth, int iheigth);
	virtual ~Buffer2D();
	void changeRatio(int newwidth, int newheigth);
	bool putToBuff(cordScr placeCords, CScreenPixel symbol);
};

