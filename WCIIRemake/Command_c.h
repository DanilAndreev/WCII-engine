#pragma once
#include <vector>
#include <utility>
#include <string>
#include <iostream>

using namespace std;

class Command_c {
public:
	vector <pair<string, string>> args;
public:
	Command_c(vector <pair<string, string>> inp_args) : args(inp_args) {}
	Command_c(string arg);
	Command_c();
	~Command_c();
	void printCommand(string imessage);
	void printCommand();
public:
	friend bool operator==(const Command_c& left, string right);
};
