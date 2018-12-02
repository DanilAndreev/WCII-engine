#include "pch.h"
#include "Obj.h"


Obj::Obj() {
	this->className = "Obj";
}

Obj::Obj(const char* className) {
	this->className = className;
}

Obj::~Obj() {
}

void Obj::setClassName(const char* className) {
	this->className = className;
}

const char* Obj::getClassName() {
	return this->className;
}



