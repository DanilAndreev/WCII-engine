#include "pch.h"
#include "EV_CScreen_Controlled.h"


EV_CScreen_Controlled::EV_CScreen_Controlled(cordScr icords, int iwidth, int iheigth, CScreenPixel dafaultFill, int ilayer) : EV_CScreen(icords, iwidth, iheigth, dafaultFill, ilayer) {
	this->calcPlacemnt();
}


EV_CScreen_Controlled::~EV_CScreen_Controlled() {
}

//directions: 1 - up , 2 - down, 3 - left , 4 - right 
void EV_CScreen_Controlled::move(int direction) {
	cordScr newCords = this->cords;
	switch (direction) {
	case 1:
		newCords.y -= 1;
		break;
	case 2:
		newCords.y += 1;
		break;
	case 3:
		newCords.x -= 1;
		break;
	case 4:
		newCords.x += 1;
		break;
	}
	if (parentScreen) {
		cordScr diamCord(newCords.x + this->width, newCords.y + this->heigth);
		this->calcPlacemnt();

		switch (direction) {
		case 1:
			if (diamCord.y >= cordScr(parentScreen->width, parentScreen->heigth).y) {
				this->cords = newCords;
			}
			break;
		case 2:
			if (cordScr(0, 0).y >= newCords.y) {
				this->cords = newCords;
			}
			break;
		case 3:
			if (diamCord.x >= cordScr(parentScreen->width, parentScreen->heigth).x) {
				this->cords = newCords;
			}
			break;
		case 4:
			if (cordScr(0, 0).x >= newCords.x) {
				this->cords = newCords;
			}
			break;
		}
	}
}

void EV_CScreen_Controlled::calcPlacemnt() {
	cordScr targetCords = this->cords;
	if (!parentScreen) {
		this->cords = targetCords;
		return;
	}
	if (this->width < parentScreen->width) {
		targetCords.x = (parentScreen->width - this->width) / 2 - 1;
	}
	if (this->heigth < parentScreen->heigth) {
		targetCords.y = (parentScreen->heigth - this->heigth) / 2 - 1;
	}
	this->cords = targetCords;
	return;
}
