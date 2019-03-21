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
public:
	eventReturnData(ID objId, cordScr cords, string className); //input :  ID objectId, cordScr cords, string Class Name
	eventReturnData(ID objId, cordScr cords) : eventReturnData(objId, cords, "Default") {} //input :  ID objectId, cordScr cord (class name will be "Default")
	virtual ~eventReturnData();
};

