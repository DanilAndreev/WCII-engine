#pragma once
#include "pch.h"
#include "Obj.h"

class MScreen;

// структура данных для хранения координат
struct cordScr : public Obj {
	int x;
	int y;
	cordScr(int x, int y) : x(x) , y(y) {}
	cordScr() : x(0), y(0) {}
};

// Класс для всех елементов, которые будут рисоваться на екране (наследовать от него)
class Screenable : public Obj {
	protected:
		cordScr cords;
		int width;
		int heigth;
		MScreen* scr;
	public:
		Screenable(cordScr cords, int width, int heigth, MScreen* scr);
		Screenable();
		virtual ~Screenable();
		cordScr getCord(); //возвращает координаты 
		int setCord(cordScr cords); // установить координаты
		int setup(cordScr cords, int width, int heigth, MScreen* scr); // инициализировать елемент (передаем координаты, куда залепить елемент, его ширину и высоту и указатель на екран, где он будет отрисовываться)
		virtual void render(); // отрисоваться(просчитаться)
};

