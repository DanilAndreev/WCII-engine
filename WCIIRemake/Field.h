#pragma once
#include "pch.h"
#include "Screenable.h"

class Unit;

class Field : public Screenable {
	private:
		int fieldLen;
		DynArr** field;
	protected:
		DynArr* members;
	public:
		DynArr** getField();
		DynArr* getMembers();
		Field(int width, int heigth); 
		Field();
		virtual ~Field();
		void freeElements(); // Удалить всех детей поля(из пямяти, указатели осстанутся, но будут указывать в небо)
		int setCell(cordScr cordsNew, Unit * target); // установить на клетку с данными координатам данный юнит
		int changeCell(cordScr cords, Unit * target); // поменять клетку(прыгнуть в клетку с данными координатами)
		virtual void render(); // отрисоваться(просчитаться)
		bool checkFree(cordScr cords, int type); // проверить клетку на наличие юнита даного типа (вернет истину если нету и ложь если есть)
		//virtual void operateEvent(Command_c command);
};

