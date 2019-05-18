#include "pch.h"
#include "Eventable.h"

extern Console* defaultConsole;

Eventable::Eventable() {
}


Eventable::~Eventable() {
}

void Eventable::fillEventPatterns() {
}

bool Eventable::operateEvent(Command_c* command, bool showHelp) {
	for (unsigned int i = 0; i < this->eventPatterns.size(); i++) {
		if (eventPatterns[i] ^= *command) {
			eventPatterns[i].callback_func(command, this);
			return true;
		}
	}
	if (showHelp) {
		defaultConsole->error("Invalid command");
		for (unsigned int i = 0; i < this->eventPatterns.size(); i++) {
			if (eventPatterns[i] == *command) {
				defaultConsole->warning(string("Usage: ") + eventPatterns[i].usingHelpMessage);
			}
		}
	}
	return false;
}

void Eventable::catchEvent(Command_c* command, bool showHelp) {
}

EventPattern Eventable::searchPatternByName(string name) {
	for (unsigned int i = 0; i < this->eventPatterns.size(); i++) {
		if (this->eventPatterns[i].name == name) {
			return this->eventPatterns[i];
		}
	}
	return EventPattern("", "", "", NULL);
}

EventPattern Eventable::searchPatternByCommandName(string commandName) {
	for (unsigned int i = 0; i < this->eventPatterns.size(); i++) {
		if (this->eventPatterns[i] == commandName) {
			return this->eventPatterns[i];
		}
	}
	return EventPattern("", "", "", NULL);
}
