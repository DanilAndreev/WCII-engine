#include "pch.h"
#include "Field.h"

extern Console* defaultConsole;

Field::Field(int width, int heigth) {
	fieldLen = width * heigth;

	this->width = width;
	this->heigth = heigth;
	// OLD code
/*
	field = new DynArr*[fieldLen];
	memset(field, 0, fieldLen*sizeof(Unit*));
	for (int i = 0; i < fieldLen; i++) {
		field[i] = new DynArr();
	}
*/
	members = new DynArr();
}

Field::Field() {
	Field(30, 30);
}


Field::~Field() {
//OLD code
/*
	delete [] field;
*/
	delete members;
}


// OLD code
/*
DynArr ** Field::getField() {
	return this->field;
}
*/

DynArr* Field::getMembers() {
	return members;
}


void Field::freeElements() {
	members->freeItems();
}

bool Field::checkFree(cordScr cords, int type) {
	if (cords.x >= this->width || cords.y >= this->heigth) {
		return false;
	}

// OLD  code
/*  
	DynArr* cell = field[cords.y*width + cords.x];
	if (cell->count() == 0) {
		return true;
	}
	for (int i = 0; i < cell->count(); i++) {
		if (((Unit*)(cell->get(i)))->getType() != type) {
			return true;
		}
		return false;
	}
	return false;
*/

	for (int i = 0; i < members->count(); i++) {
		Unit* unit = (Unit*)(members->get(i));
		if (unit->getCord() == cords && unit->getType() == type) {
			return false;
		}
	}
	return true;
}





int Field::setCell(cordScr cords, Unit* target) {
	if (members->search(target) == -1) {
		if (checkFree(cords, target->getType())) {
			target->setup(cords, 1, 1, this->scr);
// OLD code
//			field[cords.y*width + cords.x]->add(target);
			members->add(target);
			return 1;
		}
	}
	return 0;
}


int Field::changeCell(cordScr cordsNew, Unit* target) {
	int foundInd = members->search(target);
	if (foundInd > -1) {
		if (checkFree(cordsNew, target->getType())) {
// OLD code
/*
			cordScr cordsPrev = ((Screenable*)members->get(foundInd))->getCord();
			field[cordsPrev.x*width + cordsPrev.y]->del(target);
			field[cordsNew.y*width + cordsNew.x]->add(target);
*/
			target->setCord(cordsNew);
			return 1;
		}
	}
	return 0;
}

void Field::render() {

	for (int i = 0; i < members->count(); i++) {
		((Screenable*)(members->get(i)))->render();
	}


}

bool Field::classifyEvent(Command_c command) {
	if (command == "select") {
		
	}
	return false;
}

void Field::operateEvent(Command_c command) {
	//TODO: operate for itself
	for (int i = 0; i < members->count(); i++) {
		members->get(i)->operateEvent(command);
	}
}
