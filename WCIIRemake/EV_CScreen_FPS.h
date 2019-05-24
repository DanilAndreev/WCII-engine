#pragma once
#include "EV_CScreen.h"
class EV_CScreen_FPS : public EV_CScreen {
protected:
	ThreadId ScreenDrawingTHREADDescriptor; // descriptor of Screen drawin thread
	int frameRate; // frames per second
	int* team;
	//int defaultTeam;
public:
	EV_CScreen_FPS(cordScr icords, int iwidth, int iheigth, CScreenPixel dafaultFill, int ilayer, int* iteam);
	~EV_CScreen_FPS();
	int* getTeam();
	void setTeam(int* newTeam);
	void setFrameRate(int newFrameRate); // setts current frame rate with input
	const int getFrameRate(); // returns current farme rate
protected:
	virtual void fillEventPatterns(); // fills the event presets with EV_CScreen_FPS events
public:	//EV_CScreen_FPS EVENTS
	static void exitGameCommand(Command_c* command, Eventable* oParent);
	static void stopThreadsCommand(Command_c* command, Eventable* oParent);



};

