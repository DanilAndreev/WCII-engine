#pragma once
#include "Placable.h"
#include "Renderable.h"
#include "CScreenPixel.h"
#include "Buffer2D.h"
#include "WColors.h"
#include "Obj.h"
#include <memory>
#include <vector>
#include <Windows.h>
#include <iostream>


using namespace std;

class CScreen : public Buffer2D, public Renderable, public Placable, public Obj {
public:
	CScreenPixel fill;
public:
	vector <Renderable*> members;
public:
	CScreen(cordScr icords, int iwidth, int iheigth, CScreenPixel dafaultFill, int ilayer);
	CScreen(int iwidth, int iheigth) : CScreen(cordScr(0, 0), iwidth, iheigth, CScreenPixel(), 1) {}
	CScreen() : CScreen(cordScr(0, 0), 0, 0, CScreenPixel(), 1) {}
	virtual ~CScreen();
	void addMember(Renderable* member);
	void clearScreenBuff();
	virtual void render(int layer);
	virtual void render();
	void draw();
	void draw(CScreenPixel fill);
};

