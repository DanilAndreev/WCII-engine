#pragma once
#include "Placable.h"
#include "Renderable.h"
#include "Obj.h"
#include "CScreenPixel.h"
#include "EV_CScreen_Controlled.h"

const int SELECTOR_ATTACK = 1;
const int SELECTOR_MOVE = 2;


class CS_Selector : public Placable, public Renderable, public Obj{
protected:
	ID ConComConId;
	CScreenPixel symbol;
	EV_CScreen_Controlled* controlledScreen;
public:
	cordScr cordFix1;
	cordScr cordFix2;
	int operation;
	bool selectingFirst;
public:
	CS_Selector(ID CccID, EV_CScreen_Controlled* icontrolledScreen);
	~CS_Selector();
	void setCCCID(ID CccID);
	void catchEvent(Command_c * command, bool showHelp);
	void operateKey(int keyid);
public:
	virtual void render();
	cordScr calculateSelectorCordOnControlled();
	virtual void render(int layer);
protected:
	void select();
	void throwCommand();
	void move(int direction);
protected:
	virtual void fillEventPatterns();
public:	//CS_Selector EVENTS
	static void keyPressIdCommand(Command_c* command, Eventable* oParent);
};

