#pragma once
#include "pch.h"
#include "Screenable.h"


class FieldPreset {
public:
	int width;
	int heigth;
	
};

class Unit;

class Field : public Screenable {
	private:
		int fieldLen;
	protected:
		DynArr* members;
	public:
		Field(int width, int heigth);
		Field() : Field(30, 30) {}
		Field(FieldPreset preset) : Field(preset.width, preset.heigth) {}
		virtual ~Field();
		DynArr* getMembers();
		void freeElements(); // Удалить всех детей поля(из пямяти, указатели останутся, но будут указывать в небо)
		int setCell(cordScr cordsNew, Unit * target); // установить на клетку с данными координатам данный юнит
		int changeCell(cordScr cords, Unit * target); // поменять клетку(прыгнуть в клетку с данными координатами)
		virtual void render(); // отрисоваться(просчитаться)
		bool checkFree(cordScr cords, int type); // проверить клетку на наличие юнита даного типа (вернет истину если нету и ложь если есть)
		bool classifyEvent(Command_c* command);
		virtual void operateEvent(Command_c* command);
		//Field commands(Events)
		bool spawnEvent(Command_c* command);
		bool writeEvent(Command_c* command);
};

