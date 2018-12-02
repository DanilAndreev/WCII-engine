#pragma once
#include "pch.h"
#include "Screenable.h"
#include "DynArr.h"



class MScreen : public Screenable {
private:
	DynArr* elements;
	int width;
	int height;
	int bufLen;
	char *buff;
public:
	MScreen(int width, int heigth);
	MScreen() : MScreen(80, 25) {}
	void setRatio(int width, int heigth);
	virtual ~MScreen();
	void freeElements();
	char* getBuff();
	int getWidth();
	int getHeight();
	int putToBuff(cordScr cords, char c);
	int addElement(cordScr cords, int width, int heigth, Screenable* element);
	void initBuff();
	void clear();
	void draw();
	virtual void render();
};
