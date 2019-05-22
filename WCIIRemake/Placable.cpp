#include "pch.h"
#include "Placable.h"



Placable::~Placable() {
}

cordScr Placable::getCords() {
	return this->cords;
}

void Placable::setCords(cordScr newcords) {
	this->cords = newcords;
}
