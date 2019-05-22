#include "pch.h"
#include "EV_CScreen_Controlled.h"


EV_CScreen_Controlled::EV_CScreen_Controlled(cordScr icords, int iwidth, int iheigth, CScreenPixel dafaultFill, int ilayer) : EV_CScreen(icords, iwidth, iheigth, dafaultFill, ilayer) {

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
/*
		cout << "newCords: " << newCords << endl;
		cout << "diamCord: " << diamCord << endl;
		cout << "cordScr(ps->w, ps->h): " << cordScr(parentScreen->width, parentScreen->heigth) << endl;
*/
		if (cordScr(0, 0) >= newCords && diamCord >= cordScr(parentScreen->width, parentScreen->heigth)) {
			this->cords = newCords;
		}
	}
}
