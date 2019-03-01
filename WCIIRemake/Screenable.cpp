#include "pch.h"
#include "Screenable.h"


Screenable::Screenable(cordScr cords, int width, int heigth, MScreen* scr) {
	this->cords.x = cords.x;
	this->cords.y = cords.y;
	this->scr = scr;
	this->width = width;
	this->heigth = heigth;
}

Screenable::Screenable() {
	cordScr cords;
	cords.x = 0;
	cords.y = 0;
	Screenable(cords,0,0,NULL);
}



Screenable::~Screenable() {
}

cordScr Screenable::getCord() {
	return this->cords;
}

int Screenable::setCord(cordScr cords) {
	if (cords.x >= 0 && cords.y >= 0) {
		this->cords = cords;
		return 1;
	}
	return 0;
}

int Screenable::setup(cordScr cords, int width, int heigth, MScreen* scr) {
	this->cords = cords;
	this->scr = scr;
	this->width = width;
	this->heigth = heigth;
	return 1;
}



void Screenable::render() {
}
