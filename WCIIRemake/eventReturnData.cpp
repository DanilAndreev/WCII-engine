#include "pch.h"
#include "eventReturnData.h"


eventReturnData::eventReturnData(ID objId, cordScr cords, string className) {
	this->objId = objId;
	this->cords = cords;
	this->className = className;
}


eventReturnData::~eventReturnData() {
}


