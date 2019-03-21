#pragma once
#include "Unit.h"
#include "MoveToTHREAD.h"
#include "AttackTHREAD.h"

class LiveUnit : public Unit {
private:
	cordScr moveDest;
	ThreadId MoveToTHRDDescriptor;
	ThreadId AttackTHRDDescriptor;
public:
	LiveUnit(char value, int type, Field* field, int health, int team, int attackLength);
	LiveUnit() : LiveUnit('d', 1, NULL, 100, 0, 0) {}
	~LiveUnit();
	ThreadId getMoveToTHRDDescriptor();
	cordScr* getMoveDest();
	bool goTo(cordScr* dest);
	bool attack();
private:
	int findPath(cordScr destC); // запустить поиск пути(в процессе)
	int move(int direction); //подвинуться на поле, direction: 1-up,2-down,3-rigth,4-left (нужно дописать еще 4 движения)
	bool classifyEvent(Command_c* command);
	virtual void operateEvent(Command_c* command);
	virtual void stopAllThreads();
//LIVEUNIT COMMANDS(EVENTS)
protected:
	bool tpEvent(Command_c* command);
	bool moveEvent(Command_c* command);
	bool stopEvent(Command_c * command);
	bool attackEvent(Command_c* command);
};

