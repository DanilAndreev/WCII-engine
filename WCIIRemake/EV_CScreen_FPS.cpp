#include "pch.h"
#include "EV_CScreen_FPS.h"

extern ThreadDescriptor* gameThreads;


EV_CScreen_FPS::EV_CScreen_FPS(cordScr icords, int iwidth, int iheigth, CScreenPixel dafaultFill, int ilayer) : EV_CScreen(icords, iwidth, iheigth, dafaultFill, ilayer) {
	this->ScreenDrawingTHREADDescriptor = 0;
	this->frameRate = 24;

	ScreenDrawindTHREAD* screenDrawingThread = new ScreenDrawindTHREAD(this);
	this->ScreenDrawingTHREADDescriptor = screenDrawingThread->getDescriptor();
	screenDrawingThread->startThread();
}


EV_CScreen_FPS::~EV_CScreen_FPS() {
	gameThreads->stopThread(this->ScreenDrawingTHREADDescriptor);
}

void EV_CScreen_FPS::setFrameRate(int newFrameRate) {
	this->frameRate = newFrameRate;
}

const int EV_CScreen_FPS::getFrameRate() {
	return this->frameRate;
}

void EV_CScreen_FPS::fillEventPatterns() {
	const EventPattern exitGamePattern(
		"exitgame",
		"exitGamePattern",
		"exitgame",
		EV_CScreen_FPS::exitGameCommand);
	const EventPattern stopThreadsPattern(
		"stop threads",
		"stopThreadsPattern",
		"stop threads {flags}",
		EV_CScreen_FPS::stopThreadsCommand);

	this->eventPatterns.push_back(exitGamePattern);
	this->eventPatterns.push_back(stopThreadsPattern);
}


// exit game
void EV_CScreen_FPS::exitGameCommand(Command_c* command, Eventable* oParent) {
	EV_CScreen_FPS* parent = dynamic_cast<EV_CScreen_FPS*>(oParent);
	if (!parent) {
		return;
	}
	gameThreads->stopThread(parent->ScreenDrawingTHREADDescriptor);
}

// stop threads
void EV_CScreen_FPS::stopThreadsCommand(Command_c* command, Eventable* oParent) {
	EV_CScreen_FPS* parent = dynamic_cast<EV_CScreen_FPS*>(oParent);
	if (!parent) {
		return;
	}
	HANDLE temp_handle;
	if ((temp_handle = gameThreads->stopThread(parent->ScreenDrawingTHREADDescriptor)) != NULL) {
		eventReturnDataHandle* temp = new eventReturnDataHandle(parent->id, parent->className, temp_handle);
		command->data.push_back(temp);
	}
}
