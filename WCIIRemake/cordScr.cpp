#include "pch.h"
#include "cordScr.h"

bool operator==(const cordScr left, const cordScr right) {
	return (left.x == right.x) && (left.y == right.y);
}

bool operator!=(const cordScr left, const cordScr right) {
	return (left.x != right.x) || (left.y != right.y);
}

bool operator>(const cordScr left, const cordScr right) {
	return left.x > right.x && left.y > right.y;
}

bool operator<(const cordScr left, const cordScr right) {
	return left.x < right.x && left.y < right.y;
}

bool operator>=(const cordScr left, const cordScr right) {
	return left.x >= right.x && left.y >= right.y;
}

bool operator<=(const cordScr left, const cordScr right) {
	return left.x <= right.x && left.y <= right.y;
}

cordScr operator + (const cordScr left, const cordScr right) {
	cordScr temp(left.x + right.x, left.y + right.y);
	return temp;
}

cordScr operator - (const cordScr left, const cordScr right) {
	cordScr temp(left.x - right.x, left.y - right.y);
	return temp;
}

cordScr operator+(const cordScr left, const int right) {
	cordScr temp(left.x + right, left.y + right);
	return temp;
}

cordScr operator-(const cordScr left, const int right) {
	cordScr temp(left.x - right, left.y - right);
	return temp;
}

ostream& operator<<(ostream& stream, cordScr cord) {
	stream << cord.x << " " << cord.y;
	return stream;
}



float cordScr::lineLength(cordScr cord1, cordScr cord2) {
	if (cord1.x < 0 || cord1.y < 0 || cord2.x < 0 || cord2.y < 0) {
		return -1;
	}
	return sqrt(sqr(cord2.x - cord1.x) + sqr(cord2.y - cord1.y));
}

int cordScr::sqr(int input) {
	return input * input;
}



