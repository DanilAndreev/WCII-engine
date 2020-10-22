#pragma once
#include "WColors.h"

class CScreenPixel {
public:
	char symbol;
	WORD color;
public:
	CScreenPixel(char isymbol, WORD icolor) : symbol(isymbol), color(icolor) {}
	CScreenPixel() : symbol(' '), color(COLOR_WHITE) {}
	~CScreenPixel();
};

