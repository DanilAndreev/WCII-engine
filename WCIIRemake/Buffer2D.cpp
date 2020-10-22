#include "pch.h"
#include "Buffer2D.h"


Buffer2D::Buffer2D(int iwidth, int iheigth) {
	this->rebooting = false;
	this->width = iwidth;
	this->heigth = iheigth;
	Buff = NULL;
	changeRatio(iwidth, iheigth);
}

Buffer2D::~Buffer2D() {
	for (int i = 0; i < width * heigth; i++) {
		delete Buff[i];
	}
	delete[] Buff;
}

void Buffer2D::changeRatio(int newwidth, int newheigth) {
	this->rebooting = true;
	if (Buff) {
		for (int i = 0; i < heigth * width; i++) {
			delete Buff[i];
		}
		delete Buff;
		Buff = NULL;
	}

	this->width = newwidth;
	this->heigth = newheigth;

	Buff = new CScreenPixel * [width * heigth];
	for (int i = 0; i < heigth * width; i++) {
		Buff[i] = new CScreenPixel();
	}
	this->rebooting = false;
}

bool Buffer2D::putToBuff(cordScr placeCords, CScreenPixel symbol) {
	if (!rebooting) {
		if (cordScr(0, 0) <= placeCords && placeCords < cordScr(width, heigth)) {
			*(Buff[placeCords.y * width + placeCords.x]) = symbol;
			return true;
		}
	}
	return false;
}
