#pragma once

#include "pch.h"
#include "Screenable.h"
#include "Threadable.h"
#include "FastPath.h"
#include <ctime>
#include <stdlib.h>

class Unit : public Screenable, public Threadable{
protected:
	Field* field;
	char value;//for debug
	int type;
	cordScr moveDest;

	bool threadFlag;
public:

//	Unit(Unit** field);
	Unit(cordScr cords, char value,int type, Field* field);
	Unit(cordScr cords, Field* field) : Unit(cords, 'd', 1, field) {}
	Unit(cordScr cords, int type, Field* field) : Unit(cords, 'd', type, field) {}
	Unit(char value, int type, Field* field) : Unit(cordScr(0, 0), value, type, field) {}
	Unit(char value, Field* field) : Unit(cordScr(0, 0), value, 1, field) {}
	Unit() : Unit(cordScr(0, 0), NULL) {}
	virtual ~Unit();
	char getValue(); // возвращает символьное значение этого юнита(для проверки пока нет картинок и графики) 
	int getType(); // возвращает условный тип юнита(потом будет классификация на сухопутных, воздушных и морских юнитов)
	int move(int direction); //подвинуться на поле, direction: 1-up,2-down,3-rigth,4-left (нужно дописать еще 4 движения)
	bool goTo(cordScr* dest);
	virtual void render(); // отрисоваться(просчитаться)
	bool classifyEvent(Command_c command);
	virtual void threadFunction();
	virtual void operateEvent(Command_c command);
private:
	int findPath(cordScr destC); // запустить поиск пути(в процессе)
private:
	//UNIT COMMANDS(EVENTS)
	bool selectEvent(Command_c command);
	bool echoEvent(Command_c command);
	bool tpEvent(Command_c command);
	bool moveEvent(Command_c command);

};

