#pragma once
using namespace std;
#include <cmath>

// структура данных для хранения координат
struct cordScr/* : public Obj */ {
	int x;
	int y;
	cordScr(int x, int y) : x(x), y(y) {}
	cordScr() : x(0), y(0) {}

	friend bool operator==(const cordScr left, cordScr right) {
		return (left.x == right.x) && (left.y == right.y);
	}

	float lineLength(cordScr cord1, cordScr cord2) {
		if (cord1.x < 0 || cord1.y < 0 || cord2.x < 0 || cord2.y < 0) {
			return -1;
		}
		return sqrt(sqr(cord2.x - cord1.x) + sqr(cord2.y - cord1.y));
	}

	inline int sqr(int input) {
		return input * input;
	}

};
