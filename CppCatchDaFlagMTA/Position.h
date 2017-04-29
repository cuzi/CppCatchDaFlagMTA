#pragma once
class Position {
	int _x = -1;
	int _y = -1;
	char _c = '+';
	bool isSet = false;
public:
	Position(int x, int y, char c) : _x(x), _y(y), _c(c) {};
	Position(){};
	void set(int x, int y, char c) {
		_x = x;
		_y = y;
		_c = c;
		isSet = true;
	}
	bool isInit() {
		return !(_x == -1 && _y == -1 && _c == '+');
	}
	int getX() {
		return _x;
	}
	int getY() {
		return _y;
	}
	int getC() {
		return _c;
	}
	bool isPositionSet() {
		return isSet;
	}
};