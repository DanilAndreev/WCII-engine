#include "pch.h"
#include "Obj.h"



Obj::Obj() {
	this->className = "Obj";
	this->selected = false;
	cout << "kuku";
}

Obj::Obj(const char* className) {
	this->className = className;
	this->selected = false;
}

Obj::~Obj() {
}

void Obj::setClassName(const char* className) {
	this->className = className;
}

void Obj::operateEvent(Command_c command)
{
}

const char* Obj::getClassName() {
	return this->className;
}



