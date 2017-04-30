#pragma once
#include "Board.h"
#include <string>
class Move {
	int _clockTime = -1;
	char _boardTool = -1;
	char _direction = 0;
public:
	Move(int ct, char bt, char d) : _clockTime(ct), _boardTool(bt), _direction(tolower(d)) {};
	Move() {};
	operator int() const
	{
		return _direction;
	}
	void set(int ct, int bt, char d) {
		_clockTime = ct;
		_boardTool = tolower(bt);
		_direction = tolower(d);
	}
	int getClockTime() {
		return _clockTime;
	}
	int getTool() {
		return _boardTool;
	}
	int getDir() {
		return _direction;
	}
};