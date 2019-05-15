#include "pch.h"
#include "CommandPatterns.h"


CommandPatterns::CommandPatterns() {
}


CommandPatterns::~CommandPatterns() {
}

ConsoleCommandPattern CommandPatterns::searchPatternByName(string name) {
	for (unsigned int i = 0; i < this->commandPatterns.size(); i++) {
		if (this->commandPatterns[i].name == name) {
			return this->commandPatterns[i];
		}
	}
	return ConsoleCommandPattern("","","", NULL);
}

ConsoleCommandPattern CommandPatterns::searchPatternByCommandName(string commandName) {
	for (unsigned int i = 0; i < this->commandPatterns.size(); i++) {
		if (this->commandPatterns[i] == commandName) {
			return this->commandPatterns[i];
		}
	}
	return ConsoleCommandPattern("", "", "", NULL);
}
