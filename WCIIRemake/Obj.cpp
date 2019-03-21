#include "pch.h"
#include "Obj.h"

ID Obj::freeID = 0;

Obj::Obj() {
	this->className = "Obj";
	this->selected = false;
	this->id = getFreeId();
}

Obj::Obj(const char* className) {
	this->className = className;
	this->selected = false;
}

Obj::~Obj() {
}

ID Obj::getId()
{
	return this->id;
}

ID Obj::getFreeId() {
	return ++freeID;
}

void Obj::setClassName(const char* className) {
	this->className = className;
}

void Obj::operateEvent(Command_c* command){
}

const char* Obj::getClassName() {
	return this->className;
}



