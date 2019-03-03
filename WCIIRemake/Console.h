#pragma once
#include "Obj.h"
#include <iostream> 



using namespace std;


class Console : public Obj {
private:
public:
	Console();
	~Console();
	string getLine();
	void error(string str);
	void warning(string str);
	void message(string str);
};



