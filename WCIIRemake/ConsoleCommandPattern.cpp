#include "pch.h"
#include "ConsoleCommandPattern.h"


ConsoleCommandPattern::ConsoleCommandPattern(string command, string name, string usingHelpMessage, void (*callback_func)(Command_c*, CommandPatterns*)/*, Obj* parent*/) : Command_c(command) {
	this->name = name;
	this->usingHelpMessage = usingHelpMessage;
	this->callback_func = callback_func;
}

ConsoleCommandPattern::~ConsoleCommandPattern() {
}
