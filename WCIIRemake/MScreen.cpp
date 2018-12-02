#include "pch.h"
#include "MScreen.h"


MScreen::MScreen(int width, int heigth) {
	elements = new DynArr();
	this->height = heigth;
	this->width = width;
	buff = NULL;
	this->bufLen = height * width;
	initBuff();
}

/*MScreen::MScreen() : MScreen(80, 25) {
}*/

void MScreen::setRatio(int width, int heigth) {
	this->height = heigth;
	this->width = width;
	this->bufLen = height * width;
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
	return height;
}

int MScreen::putToBuff(cordScr cords, char c) {
	if (cords.y < height && cords.y >= 0 && cords.x < width && cords.x >= 0) {
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

	for (int y = 0; y < height; y++) {
		char *temp = new char[width + 1];
		memcpy(temp, buff + (y*width), width * sizeof(char));
		temp[width] = 0;
		printf("\n%s", temp);
		delete[] temp;
		
	}
	printf("\n-------------------------------------------------------------");


}

void MScreen::render() {
	initBuff();
	for (int i = 0; i < elements->count(); i++) {
		((Screenable*)elements->get(i))->render();
	}
	if (scr != NULL) {
		for (int y = 0; y < height; y++) {
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