#pragma once
#include "eventReturnData.h"
#include <vector>
#include <utility>
#include <string>
#include <iostream>

using namespace std;

class Command_c {
protected:
	int ParserPosition;
public:
	vector <pair<string, string>> args;
	vector <eventReturnData*> data;
public:
	Command_c(vector <pair<string, string>> inp_args) : args(inp_args), ParserPosition(0){}
	Command_c(string arg);
	Command_c(int notUsed, const char* s1, ...); // constructor for multiple strings, to finish the enter set 0 parameter; for example Command_c(1, "sdf", "sdss", 0);
	Command_c();
	~Command_c();
	void printCommand(string imessage); // prints the command to the debug console with user message
	void printCommand(); // prints the command to the console in debug mode
	bool checkFlag(string target); // returns true if it is a requested flag in this command and false in not
	int search(string target); // returns index of first matched requested value in the command or -1 if not found
public:
	friend bool operator==(const Command_c& left, string right);
	friend bool operator==(const Command_c& left, const Command_c& right);
	friend bool operator^=(const Command_c& left, const Command_c& right);
protected:
	bool readCondition(char character);
	string commandType(char character);
	pair <string, string> nextToken(string command);
	void initParser();
	bool parseCommand(string command); // Parse the command
};
