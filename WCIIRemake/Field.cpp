#include "pch.h"
#include "Field.h"

extern Console* defaultConsole;
extern GameMaster* gameMaster;


Field::Field(int width, int heigth) {
	fieldLen = width * heigth;

	this->width = width;
	this->heigth = heigth;
	members = new DynArr();
}

Field::Field() {
	Field(30, 30);
}

Field::~Field() {
	delete members;
}

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

bool Field::classifyEvent(Command_c* command) {
	if (*command == "select") {
		
	}
	return false;
}

void Field::operateEvent(Command_c* command) {
	classifyEvent(command);
	for (int i = 0; i < members->count(); i++) {
		members->get(i)->operateEvent(command);
	}
}
