#pragma once
#include "Obj.h"

using namespace std;


class Console : public Obj {
public:
	Console();
	~Console();
	string getLine();
	void error(string str);
	void warning(string str);
	void message(string str);
};



