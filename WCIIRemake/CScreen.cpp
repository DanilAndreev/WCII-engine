#include "pch.h"
#include "CScreen.h"

using namespace std;

CScreen::CScreen(cordScr icords, int iwidth, int iheigth, CScreenPixel defaultFill, int ilayer) : Buffer2D(iwidth, iheigth), Placable(icords, ilayer), Obj("CScreen") {
	this->fill = defaultFill;
	this->clearScreenBuff();
}

CScreen::~CScreen() {
	draw(CScreenPixel(' ', COLOR_BLACK));
}

void CScreen::addMember(Renderable* member) {
	members.push_back(member);
	member->setParentScreen(this);
}


void CScreen::clearScreenBuff() {
	for (int i = 0; i < heigth * width; i++) {
		*(Buff[i]) = this->fill;
	}
}


void CScreen::render(int layer) {
	this->clearScreenBuff();
	for (int i = 0; i < members.size(); i++) {
		Renderable* temp = members[i];
		if (temp) {
			temp->render(layer);
		}
	}
	if (parentScreen) {
		for (int y = 0; y < heigth; y++) {
			for (int x = 0; x < width; x++) {
				cordScr tempCords = this->cords;
				tempCords.x = x + this->cords.x;
				tempCords.y = y + this->cords.y;
				parentScreen->putToBuff(tempCords, *(Buff[y * width + x]));
			}
		}
	}
}

void CScreen::render() {
	this->render(0);
	draw();
}

void CScreen::draw() {
	for (int y = 0; y < heigth; y++) {
//		for (int x = 0; x < width; x++) {
			COORD cord;
			cord.X = this->cords.x;
			cord.Y = y + this->cords.y;
			DWORD result;
			HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
			//			WORD colorAttr = COLOR_BLUE;
			const int line_width = this->width;

			CHAR* line = new CHAR[line_width];
			WORD* colors = new WORD[line_width];
			for (int x = 0; x < line_width; x++) {
				line[x] = Buff[y * width + x]->symbol;
				colors[x] = Buff[y * width + x]->color;
			}

			WriteConsoleOutputAttribute(hStdOut, colors, line_width, cord, &result);

			WriteConsoleOutputCharacterA(hStdOut, line, line_width, cord, &result); // WriteConsoleOutputCharacter
		}
//	}
}

void CScreen::draw(CScreenPixel fill) {
	for (int y = 0; y < heigth; y++) {
		for (int x = 0; x < width; x++) {
			COORD cord;
			cord.X = x + this->cords.x;
			cord.Y = y + this->cords.y;
			DWORD result;
			HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
			WriteConsoleOutputAttribute(hStdOut, &fill.color, 1, cord, &result);

			WriteConsoleOutputCharacterA(hStdOut, &fill.symbol, 1, cord, &result); // WriteConsoleOutputCharacter
		}
	}
}


