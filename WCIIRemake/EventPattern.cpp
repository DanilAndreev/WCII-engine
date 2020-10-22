#include "pch.h"
#include "EventPattern.h"


EventPattern::EventPattern(string command, string name, string usingHelpMessage, void (*callback_func)(Command_c*, Eventable*)) : Command_c(command) {
	this->name = name;
	this->usingHelpMessage = usingHelpMessage;
	this->callback_func = callback_func;
}

EventPattern::~EventPattern() {
}
