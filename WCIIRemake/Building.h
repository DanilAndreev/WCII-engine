#pragma once
#include "Unit.h"


class Building : public Unit {
protected:

public:
	Building();
	~Building();
	bool classifyEvent(Command_c* command);
	virtual void operateEvent(Command_c* command);
	//BUILDING COMMANDS(EVENTS)
	bool produce(Command_c* command);
};

