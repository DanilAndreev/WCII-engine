#include "pch.h"
#include "Command_c.h"


Command_c::Command_c() {
	Command_c("error");
}

Command_c::Command_c(string arg) {
	pair <string, string> command;
	command.first = arg;
	command.second = "command";
	args.push_back(command);
}

Command_c::~Command_c() {
}

void Command_c::printCommand(string imessage) {
	cout << imessage << endl;
	for (unsigned int i = 0; i < args.size(); i++) {
		cout << "[" << i << "]" << "(" << args[i].second << ")'" << args[i].first << "'";
		if (i != args.size() - 1) {
			cout << " : ";
		}
	}
	cout << endl;
}

void Command_c::printCommand() {
	printCommand("");
}

bool Command_c::checkFlag(string target) {
	for (int i = 0; i < this->args.size(); i++) {
		if (target == this->args[i].first && this->args[i].second == "flag") {
			return true;
		}
	}
	return false;
}

int Command_c::search(string target) {
	for (int i = 0; i < this->args.size(); i++) {
		if (this->args[i].first == target) {
			return i;
		}
	}
	return -1;
}



bool operator==(const Command_c & left, string right) {
	return left.args[0].first == right;
}

