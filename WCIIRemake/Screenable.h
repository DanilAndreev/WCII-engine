#pragma once
#include "pch.h"
#include "Obj.h"
#include "cordScr.h"

class MScreen;



// Класс для всех елементов, которые будут рисоваться на екране (наследовать от него)
class Screenable : public Obj {
	protected:
		cordScr cords;
		int width;
		int heigth;
		MScreen* scr;
		int layer;
	public:
		Screenable(cordScr cords, int width, int heigth, MScreen* scr);
		Screenable();
		virtual ~Screenable();
		int getWidth();
		int getHeigth();
		cordScr getCord(); //возвращает координаты 
		int setCord(cordScr cords); // установить координаты
		int setup(cordScr cords, int width, int heigth, MScreen* scr); // инициализировать елемент (передаем координаты, куда залепить елемент, его ширину и высоту и указатель на екран, где он будет отрисовываться)
		virtual void render(int layer); // отрисоваться(просчитаться)
		virtual void settingUp();
};

