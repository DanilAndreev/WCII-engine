#include "pch.h"
#include "Unit.h"

/*
Unit::Unit(Unit** field) {
	this->field = field;
}


Unit::Unit() {
	Unit(NULL);
}
*/
Unit::Unit(cordScr cords, char value,int type, Field* field) {
	this->cords = cords;
	this->value = value;
	this->field = field;
	this->type = type;
}



Unit::~Unit() {
	
}

int Unit::getType() {
	return this->type;
}

char Unit::getValue() {
	return value;
}

int Unit::move(int direction) {
	switch (direction) {
		case 1: // up
			if (field->changeCell(cordScr(cords.x, cords.y - 1), this)) {
				return 1;
			}
			break;
		case 2: // down
			if (field->changeCell(cordScr(cords.x, cords.y + 1), this)) {
				return 1;
			}
			break;
		case 3: // rigth
			if (field->changeCell(cordScr(cords.x + 1, cords.y), this)) {
				return 1;
			}
			break;
		case 4: // left
			if (field->changeCell(cordScr(cords.x + 1, cords.y), this)) {
				return 1;
			}
			break;
		case 5: // left
			if (field->changeCell(cordScr(cords.x - 1, cords.y+1), this)) {
				return 1;
			}
			break;
		case 6: // left
			if (field->changeCell(cordScr(cords.x - 1, cords.y - 1), this)) {
				return 1;
			}
			break;
		case 7: // left
			if (field->changeCell(cordScr(cords.x + 1 , cords.y + 1), this)) {
				return 1;
			}
			break;
		case 8: // left
			if (field->changeCell(cordScr(cords.x + 1, cords.y - 1), this)) {
				return 1;
			}
			break;
	}
	return 0;
}

int Unit::findPath(cordScr destC) {

	return 0;
}


void Unit::render() {
	if (scr != NULL) {
		scr->putToBuff(this->cords, this->value);
	}
}


