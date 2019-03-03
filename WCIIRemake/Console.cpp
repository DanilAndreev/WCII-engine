#include "pch.h"
#include "Console.h"



Console::Console() {
}


Console::~Console() {
}

string Console::getLine() {
	string temp;
	getline(cin, temp);
	return temp;
}

void Console::error(string str) {
	cout << "Error: " << str << endl;
}

void Console::warning(string str) {
	cout << "Warning: " << str << endl;
}

void Console::message(string str) {
	cout << str << endl;
}




