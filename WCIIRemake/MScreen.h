#pragma once
#include "pch.h"
#include "Screenable.h"
#include "DynArr.h"
#include "ScreenDrawindTHREAD.h"
#include "CommandPatterns.h"


class MScreen : public Screenable, public CommandPatterns {
private:
	DynArr* elements;
//	int width;
//	int height;
	int bufLen;
	ThreadId screenDrawingTHRDDescriptor;
public:
	MScreen(int width, int heigth);
	MScreen() : MScreen(80, 25) {}
	virtual ~MScreen();
	void setRatio(int width, int heigth); // установить новый screen ratio (хз как по человечески перевести :) )
	void freeElements(); // удалить екземпл€ры всех детей екрана
	char* getBuff(); // возвращает буфер в виде массива(одномерного) символов
	int getWidth(); // возвращает ширину буфера
	int getHeight(); // возвращает высоту буфера 
	int putToBuff(cordScr cords, char c); // добавить символ в буфер по даным координатам
	int addElement(cordScr cords, int width, int heigth, Screenable* element); // добавить елемент на екран по даным координатам, указав его высоту и ширину
	void initBuff(); // инициализировать екран
	void clear(); // очистить буфер екрана
	void draw(); // отрисоватьс€ (графически)
	virtual void render(); // отрисоватьс€(просчитатьс€)
	char *buff;
	virtual void operateEvent(Command_c* command);
protected:
	virtual void fillCommandPatterns();
public:
	static void exitGameCommand(Command_c* command, CommandPatterns* oParent);
	static void renderScreenIdCommand(Command_c* command, CommandPatterns* oParent);
	static void drawScreenIdCommand(Command_c* command, CommandPatterns* oParent);
	static void stopThreadsCommand(Command_c* command, CommandPatterns* oParent);

private:
	void classifyEvent(Command_c* command);
//MScreen COMMANDS(EVENTS)
protected:
	bool exitGameEvent(Command_c* command);
	bool renderScreenEvent(Command_c* command);
	bool drawScreenEvent(Command_c* command);
	bool stopEvent(Command_c* command);
};

// exit game
// render screen id [int:id]
// draw screen id [int:id]
// stop threads

