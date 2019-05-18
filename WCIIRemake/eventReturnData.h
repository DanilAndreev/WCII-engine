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
	bool selected;
	int team;
public:
	eventReturnData(ID objId, cordScr cords, string className, int health, string valueVariable, HANDLE eventHandle, bool selected, int team) : objId(objId), cords(cords), className(className), health(health), valueVariable(valueVariable), eventHandle(eventHandle), selected(selected), team(team) {}
	eventReturnData(ID objId, cordScr cords, string className, int health, string valueVariable, HANDLE eventHandle, int team) : eventReturnData(objId, cords, className, health, valueVariable, eventHandle, false, team) {}
	eventReturnData(ID objId, cordScr cords, string className, int health, string valueVariable, HANDLE eventHandle) : eventReturnData(objId, cords, className, health, valueVariable, eventHandle, false, 0) {}
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

