#pragma once
#include "Placable.h"
#include "Renderable.h"
#include "Obj.h"
#include "CScreenPixel.h"

class CS_Selector : public Placable, public Renderable, public Obj{
protected:
	ID ConComConId;
	CScreenPixel symbol;
public:
	CS_Selector(ID CccID);
	~CS_Selector();
	void setCCCID(ID CccID);
	void catchEvent(Command_c * command, bool showHelp);
	void operateKey(int keyid);
public:
	virtual void render();
	virtual void render(int layer);
protected:
	virtual void fillEventPatterns();
public:	//CS_Selector EVENTS
	static void keyPressIdCommand(Command_c* command, Eventable* oParent);
};

