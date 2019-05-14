#pragma once
#include <cmath>
using namespace std;

// структура данных для хранения координат
struct cordScr/* : public Obj */ {
public:
	int x;
	int y;
public:
	cordScr(int x, int y) : x(x), y(y) {}
	cordScr() : x(0), y(0) {}
	float lineLength(cordScr cord1, cordScr cord2);
	int sqr(int input);
	friend bool operator==(const cordScr left, const cordScr right);
	friend bool operator!=(const cordScr left, const cordScr right);
	friend cordScr operator + (const cordScr left, const cordScr right);
	friend cordScr operator - (const cordScr left, const cordScr right);
};



