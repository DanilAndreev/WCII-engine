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
		Field(int width, int heigth);
		Field();
		virtual ~Field();
		void freeElements();
		int setCell(cordScr cordsNew, Unit * target);
		int changeCell(cordScr cords, Unit * target);
		virtual void render();
		bool checkFree(cordScr cords, int type);
};

