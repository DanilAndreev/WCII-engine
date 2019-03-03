#include "pch.h"
#include "MScreen.h"
#include <Windows.h>

MScreen::MScreen(int width, int heigth) {
	elements = new DynArr();
	this->heigth = heigth;
	this->width = width;
	buff = NULL;
	this->bufLen = heigth * width;
	initBuff();
	FPSDrawingRunning = false;
}

/*MScreen::MScreen() : MScreen(80, 25) {
}*/

void MScreen::setRatio(int width, int heigth) {
	this->heigth = heigth;
	this->width = width;
	this->bufLen = heigth * width;
}

MScreen::~MScreen() {
	delete[] buff;
	delete elements;
}
void MScreen::freeElements() {
	elements->freeItems();
}

char* MScreen::getBuff() {
	return buff;
}

int MScreen::getWidth() {
	return width;
}

int MScreen::getHeight() {
	return heigth;
}

int MScreen::putToBuff(cordScr cords, char c) {
	if (cords.y < heigth && cords.y >= 0 && cords.x < width && cords.x >= 0) {
		buff[cords.y*width + cords.x] = c;
		return 1;
	}
	return 0;
}

int MScreen::addElement(cordScr cords, int width, int heigth, Screenable* element) {
	element->setup(cords, width, heigth, this);
	elements->add(element);
	return 1;
}
void MScreen::initBuff() {
	if (buff) {
		delete[] buff;
	}
	buff = new char[bufLen];
	memset(buff, '.', bufLen * sizeof(char));
}

void MScreen::clear() {
	initBuff();
}

void MScreen::draw() {
/*
	printf("\033[0;0H"); // move cursor to 0 0
	for (int y = 0; y < height; y++) {
		char *temp = new char[width + 1];
		memcpy(temp, buff + (y*width), width * sizeof(char));
		temp[width] = 0;
		printf("\n%s", temp);
		delete[] temp;
		
	}
	printf("\n----------------------------------------------------------------------------------\n");
*/
	for (int y = 0; y < heigth; y++) {
		for (int x = 0; x < width; x++) {
			COORD cord;
			cord.X = x + this->cords.x;
			cord.Y = y + this->cords.y;
			DWORD result;
			HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
			//LPCTSTR character = (LPCTSTR) (buff[y*width + x]);
			//cout << buff[x, y] << endl;
			//WriteConsoleOutputCharacter(hStdOut, character, 1, cord, &result); // WriteConsoleOutputCharacter
			WriteConsoleOutputCharacterA(hStdOut, &buff[y*width + x], 1, cord, &result); // WriteConsoleOutputCharacter
		}
	}

}

void MScreen::render() {
	initBuff();
	for (int i = 0; i < elements->count(); i++) {
		((Screenable*)elements->get(i))->render();
	}
	if (scr != NULL) {
		for (int y = 0; y < heigth; y++) {
			for (int x = 0; x < width; x++) {
				cordScr cordsToWrite(x + cords.x, y + cords.y);
				//cordsToWrite.x = x + cords.x;
				//cordsToWrite.y = y + cords.y;
				scr->putToBuff(cordsToWrite, buff[y*width + x]);
			}
		}
	}
	else {
		draw();
	}
}

void MScreen::FPSdrawing() {
	FPSDrawingRunning = true;
	while (FPSDrawingRunning) {
		render();
		Sleep(100);
	}
	FPSDrawingRunning = false;
}

void MScreen::operateEvent(Command_c command) {
	classifyEvent(command);
}

void MScreen::threadFunction() {
	FPSdrawing();
}

void MScreen::classifyEvent(Command_c command) {
	if (command == "exitGame") {
		exitGameEvent(command);
	}
	if (command == "render") {
		renderScreenEvent(command);
	}
	if (command == "draw") {
		drawScreenEvent(command);
	}
}

//MScreen COMMANDS(EVENTS)

bool MScreen::exitGameEvent(Command_c command) {
	if (command.args.size() == 1) {
		if (FPSDrawingRunning) {
			FPSDrawingRunning = false;
			return true;
		}
	}
	return false;
}

bool MScreen::renderScreenEvent(Command_c command) {
	if (command.args.size() >= 2) {
		if (command.args[1].first != "screen") {
			return false;
		}
	}
	else {
		return false;
	}

	if (command.args.size() > 2) {
		if (command.args[2].first == "All") {
			render();
			return true;
		}
	}
	if (command.args.size() == 2 && this->selected) {
		render();
		return true;
	}
	return false;
}

bool MScreen::drawScreenEvent(Command_c command) {
	if (command.args.size() > 1) {
		if (command.args[1].first == "All") {
			draw();
			return true;
		}
	}
	if (command.args.size() == 1 && this->selected) {
		draw();
		return true;
	}
	return false;
}
