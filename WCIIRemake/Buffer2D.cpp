#include "pch.h"
#include "Buffer2D.h"


Buffer2D::Buffer2D(int iwidth, int iheigth) {
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
	//	screenBuff = (CScreenPixel**)malloc(sizeof(CScreenPixel*) * width * heigth);
	for (int i = 0; i < heigth * width; i++) {
		Buff[i] = new CScreenPixel();
	}
}

bool Buffer2D::putToBuff(cordScr placeCords, CScreenPixel symbol) {
	if (cordScr(0, 0) <= placeCords && placeCords < cordScr(width, heigth)) {
		*(Buff[placeCords.y * width + placeCords.x]) = symbol;
		return true;
	}
	return false;
}
