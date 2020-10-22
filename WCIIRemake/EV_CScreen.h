#pragma once
#include "CScreen.h"
#include "Eventable.h"

class EV_CScreen : public CScreen {
public:
	EV_CScreen(cordScr icords, int iwidth, int iheigth, CScreenPixel dafaultFill, int ilayer);
	~EV_CScreen();
	virtual void catchEvent(Command_c* command, bool showHelp);
protected:
	virtual void fillEventPatterns();
public:	//EV_CScreen EVENTS
	static void renderScreenIdCommand(Command_c* command, Eventable* oParent);
	static void renderScreenCommand(Command_c* command, Eventable* oParent);
	static void drawScreenIdCommand(Command_c* command, Eventable* oParent);
};

// exit game
// render screen id [int:id]
// render screen {flags}
// draw screen id [int:id]
// stop threads
