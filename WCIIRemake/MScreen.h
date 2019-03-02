#pragma once
#include "pch.h"
#include "Screenable.h"
#include "DynArr.h"
#include "Threadable.h"



class MScreen : public Screenable, public Threadable {
private:
	DynArr* elements;
	int width;
	int height;
	int bufLen;
	bool FPSDrawingRunning;
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
	void FPSdrawing();
	virtual void operateEvent(Command_c command);
private:
	virtual void threadFunction();
	void classifyEvent(Command_c command);
//MScreen COMMANDS(EVENTS)
	bool exitGameEvent(Command_c command);
	bool renderScreenEvent(Command_c command);
	bool drawScreenEvent(Command_c command);
};
