#include "pch.h"
#include "CommandPatterns.h"

extern Console* defaultConsole;

CommandPatterns::CommandPatterns() {
}


CommandPatterns::~CommandPatterns() {
}

bool CommandPatterns::operateConsoleCommand(Command_c* command, bool showHelp) {
	for (unsigned int i = 0; i < this->commandPatterns.size(); i++) {
		if (commandPatterns[i] ^= *command) {
			commandPatterns[i].callback_func(command, this);
			return true;
		}
	}

	if (showHelp) {
		defaultConsole->error("Invalid command");
		for (unsigned int i = 0; i < this->commandPatterns.size(); i++) {
			if (commandPatterns[i] == *command) {
				defaultConsole->warning(string("Usage: ") + commandPatterns[i].usingHelpMessage);
			}
		}
	}
	return false;
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
