#include "pch.h"
#include "Building.h"

extern GameMaster* gameMaster;

Building::Building() {
}


Building::~Building() {
}

bool Building::classifyEvent(Command_c * command) {
	if (*command == "") {

	}

	return false;
}

void Building::operateEvent(Command_c * command) {
	classifyEvent(command);
}


//BUILDING COMMANDS(EVENTS)
bool Building::produce(Command_c * command) {
	if (true) {

	}
	return false;
}





