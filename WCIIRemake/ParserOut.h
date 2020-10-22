#pragma once
#include "Obj.h"
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

class ParserOut : public Obj {
public:
	vector <pair<string, string>> args;
public:
	ParserOut(vector <pair<string, string>> inp_args) : args(inp_args) {}
	ParserOut(string arg);
	ParserOut();
	~ParserOut();
	void print(string imessage);
	void print();
	friend bool operator==(const ParserOut& left, string right);
};

