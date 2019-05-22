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

void Console::clearScreen() {
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	// Get the number of cells in the current buffer 
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X * csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR) ' ',
		cellCount,
		homeCoords,
		&count
	)) return;

	// Fill the entire buffer with the current colors and attributes 
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
	)) return;

	// Move the cursor to home 
	SetConsoleCursorPosition(hStdOut, homeCoords);
}


