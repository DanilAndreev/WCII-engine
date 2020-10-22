#pragma once
#include "EV_CScreen.h"
class EV_CScreen_Controlled : public EV_CScreen {
public:
	EV_CScreen_Controlled(cordScr icords, int iwidth, int iheigth, CScreenPixel dafaultFill, int ilayer);
	~EV_CScreen_Controlled();
	void move(int direction);
	void calcPlacemnt();
};

