#pragma once

#include "Point.h"

class Snake {
	enum {SIZE = 5};
	enum keyOptions {UP, DOWN, LEFT, RIGHT, STOP, _keyOptionsSize};
	Point _body[SIZE];
	char _keys[_keyOptionsSize];
	int _head = 0;
	int tail() {
		return (_head - 1 + SIZE) % SIZE;
	}
public:
	void setKeys(const char* keys);
	void move();
	void notifyKeyHit(char ch);
	void setPoint(const Point& p) {
		_body[_head] = p;
	}
	bool isOn(const Point& p) {
		return _body[_head] == p;
	}
private:
	void setDirection(Direction d) {
		_body[_head].setDirection(d);
	}
	void stop() {
		_body[_head].stop();
	}
	void changeDirOccasionally() {
		if (rand() % 20 == 0) {
			_body[_head].changeDir();
		}
	}
};
