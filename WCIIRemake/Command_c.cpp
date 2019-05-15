#include "pch.h"
#include "Command_c.h"

bool compareArg(pair<string, string> firstArg, pair<string, string> secondArg);


Command_c::Command_c() {
	ParserPosition = 0;
	Command_c("error");
}

Command_c::Command_c(string arg) {
/*
	ParserPosition = 0;
	pair <string, string> command;
	command.first = arg;
	command.second = "command";
	args.push_back(command);
*/
	this-parseCommand(arg);
}

Command_c::Command_c(int notUsed, const char* s1, ...) {
	ParserPosition = 0;
	string result;
	const char** ptr = &s1;
	while (*ptr) {
		result += *ptr;
		result += " ";
		ptr++;
	}
	parseCommand(result);
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

bool operator^=(const Command_c& left, const Command_c& right) {
	if (left.args.size() > right.args.size()) {
		return false;
	}
	for (int i = 0; i < left.args.size(); i++) {
		if (!compareArg(left.args[i], right.args[i])) {
			return false;
		}
	}
	if (right.args.size() > left.args.size()) {
		for (int i = left.args.size(); i < right.args.size(); i++) {
			if (right.args[i].second != "flag") {
				return false;
			}
		}
	}
	return true;
}


//Parser
bool Command_c::readCondition(char character) {
	if ((character != ' ') && character != 0) {
		return true;
	}
	return false;
}

string Command_c::commandType(char character) {
	if (character == '-') {
		return "flag";
	}
	if (isalpha(character)) {
		return "command";
	}
	if (isdigit(character)) {
		return "number";
	}
	return "unknown";
}

pair <string, string> Command_c::nextToken(string command) {
	bool readBegin = true;
	pair <string, string> temp;
	while (!readCondition(command[ParserPosition])) {
		if (command[ParserPosition] == 0) {
			temp.first = "\0";
			temp.second = "end";
			return temp;
		}
		ParserPosition++;
	}


	while (readCondition(command[ParserPosition])) {
		temp.first += command[ParserPosition];
		if (readBegin) {
			temp.second = commandType(temp.first[0]);
		}
		readBegin = false;
		ParserPosition++;
	}
	return temp;
}


void Command_c::initParser() {
	ParserPosition = 0;
}

bool Command_c::parseCommand(string command)
{
	initParser();
	if (command.length() == 0) {
		args.clear();
		pair <string, string> command;
		command.first = "empty";
		command.second = "command";
		args.push_back(command);
		return false;
	}
	this->args.clear();
	pair <string, string> temp;
	temp = nextToken(command);
	for (int i = 0; temp.second != "end"; i++) {
		this->args.push_back(temp);
		temp = nextToken(command);
	}
	return true;
}

bool compareArg(pair<string, string> firstArg, pair<string, string> secondArg) {
	if (firstArg.first == "input_number" && secondArg.second != "number") {
		return false;
	}
	if (firstArg.first == "input_command" && secondArg.second != "command") {
		return false;
	}
	
	return true;
}
