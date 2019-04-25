#pragma once
#include "eventReturnData.h"
#include <vector>
#include <utility>
#include <string>
#include <iostream>

using namespace std;

class Command_c {
public:
	vector <pair<string, string>> args;
	vector <eventReturnData> data;
public:
	Command_c(vector <pair<string, string>> inp_args) : args(inp_args) {}
	Command_c(string arg);
	Command_c();
	~Command_c();
	void printCommand(string imessage); // prints the command to the debug console with user message
	void printCommand(); // prints the command to the console in debug mode
	bool checkFlag(string target); // returns true if it is a requested flag in this command and false in not
	int search(string target); // returns index of first matched requested value in the command or -1 if not found
public:
	friend bool operator==(const Command_c& left, string right);
};
