#pragma once
#include "ID.h"
#include "cordScr.h"
#include <string>
#include <vector>

using namespace std;

class eventReturnData {
public:
	ID objId;
	string className;
public:
	eventReturnData(ID objId, string className) : objId(objId), className(className) {}
	eventReturnData(ID objId) : eventReturnData(objId, "Default") {}
	virtual ~eventReturnData();
};


class eventReturnDataRenderData : public eventReturnData {
public:
	cordScr cords;
	int layer;
	string valueVariable;
public:
	eventReturnDataRenderData(ID objId, string className, cordScr cords, int layer, string valueVariable) : eventReturnData(objId, className), cords(cords), layer(layer), valueVariable(valueVariable) {}
	eventReturnDataRenderData(ID objId, string className, cordScr cords) : eventReturnDataRenderData(objId, className, cords, 0, string(" ")) {}
	virtual ~eventReturnDataRenderData() {}
};

class eventReturnDataHandle : public eventReturnData {
public:
	HANDLE handle;
public:
	eventReturnDataHandle(ID objId, string className, HANDLE handle) : eventReturnData(objId, className), handle(handle) {}
	virtual ~eventReturnDataHandle() {}
};


class eventReturnDataTeamInfo : public eventReturnData {
public:
	int team;
	vector<int> friendTeams;
public:
	eventReturnDataTeamInfo(ID objId, string className, int team, vector<int> friendTeams) : eventReturnData(objId, className), team(team), friendTeams(friendTeams) {}
	eventReturnDataTeamInfo(ID objId, string className, int team) : eventReturnDataTeamInfo(objId, className, team, vector<int>()) {}
	virtual ~eventReturnDataTeamInfo() {}
};


class eventReturnDataUnitInfo : public eventReturnData {
public:
	cordScr cords;
	string className;
	int health;
	string valueVariable;
	HANDLE eventHandle;
	bool selected;
	int team;
	int layer;
public:
	eventReturnDataUnitInfo(ID objId, cordScr cords, string className, int health, string valueVariable, HANDLE eventHandle, bool selected, int team) : eventReturnData(objId, className),
		cords(cords), className(className), health(health), valueVariable(valueVariable), eventHandle(eventHandle), selected(selected), team(team), layer(0) {}
	eventReturnDataUnitInfo(ID objId, cordScr cords, string className, int health, string valueVariable, HANDLE eventHandle, int team) :
		eventReturnDataUnitInfo(objId, cords, className, health, valueVariable, eventHandle, false, team) {}
	eventReturnDataUnitInfo(ID objId, cordScr cords, string className, int health, string valueVariable, HANDLE eventHandle) :
		eventReturnDataUnitInfo(objId, cords, className, health, valueVariable, eventHandle, false, 0) {}
	eventReturnDataUnitInfo() : eventReturnData(0), cords(cordScr(0,0)), className(string()), health(0), valueVariable(string()), eventHandle(0), selected(0), team(0), layer(0) {}
	/*
	eventReturnData(ID objId, cordScr cords, string className); //input :  ID objectId, cordScr cords, string Class Name
	eventReturnData(ID objId, cordScr cords) : eventReturnData(objId, cords, "Default") {} //input :  ID objectId, cordScr cord (class name will be "Default")
	eventReturnData(HANDLE handle);
*/
	eventReturnDataUnitInfo(ID objId, cordScr cords, string className) : eventReturnDataUnitInfo(objId, cords, className, 0, "d", NULL) {} //input :  ID objectId, cordScr cords, string Class Name
	eventReturnDataUnitInfo(ID objId, cordScr cords) : eventReturnDataUnitInfo(objId, cords, "Default", 0, "d", NULL) {} //input :  ID objectId, cordScr cord (class name will be "Default")
	eventReturnDataUnitInfo(HANDLE handle) : eventReturnDataUnitInfo(0, cordScr(), "Default", 0, "d", handle) {}
//	virtual ~eventReturnDataUnitInfo();
};

