#pragma once
#include "Obj.h"
#include <iostream> 
#include <conio.h>


using namespace std;


class Console : public Obj {
private:
public:
	Console();
	~Console();
	string getLine();
	KeyID readKey();
	void error(string str);
	void warning(string str);
	void message(string str);
};



