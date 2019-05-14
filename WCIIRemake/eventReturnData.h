#pragma once
#include "ID.h"
#include "cordScr.h"
#include <string>

using namespace std;


class eventReturnData {
public:
	ID objId;
	cordScr cords;
	string className;
	int health;
	string valueVariable;
	HANDLE eventHandle;
public:
	eventReturnData(ID objId, cordScr cords, string className, int health, string valueVariable, HANDLE eventHandle) : objId(objId), cords(cords), className(className), health(health), valueVariable(valueVariable), eventHandle(eventHandle) {}
/*
	eventReturnData(ID objId, cordScr cords, string className); //input :  ID objectId, cordScr cords, string Class Name
	eventReturnData(ID objId, cordScr cords) : eventReturnData(objId, cords, "Default") {} //input :  ID objectId, cordScr cord (class name will be "Default")
	eventReturnData(HANDLE handle);
*/
	eventReturnData(ID objId, cordScr cords, string className) : eventReturnData(objId, cords, className, 0, "d", NULL) {} //input :  ID objectId, cordScr cords, string Class Name
	eventReturnData(ID objId, cordScr cords) : eventReturnData(objId, cords, "Default", 0, "d", NULL) {} //input :  ID objectId, cordScr cord (class name will be "Default")
	eventReturnData(HANDLE handle) : eventReturnData(0, cordScr(), "Default", 0, "d", handle) {}
	virtual ~eventReturnData();
};

