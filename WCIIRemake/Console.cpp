#include "pch.h"
#include "Console.h"



Console::Console() {
	setDescription("Console");
}

Console::~Console() {
}

string Console::getLine() {
	string temp;
	getline(cin, temp);
	return temp;
}

KeyID Console::readKey() {
	return _getch();
}

void Console::error(string str) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, COLOR_RED);
	cout << "Error: " << str << endl;
	SetConsoleTextAttribute(hStdOut, COLOR_WHITE);
}

void Console::warning(string str) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, COLOR_BLUE);
	cout << "Warning: " << str << endl;
	SetConsoleTextAttribute(hStdOut, COLOR_WHITE);
}

void Console::message(string str) {
	cout << str << endl;
}




