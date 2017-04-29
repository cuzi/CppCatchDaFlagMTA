#pragma once
#include "Board.h"

class Move {
	int _clockTime = -1;
	int _boardTool = -1;
	char _direction = '0';
public:
	Move(int ct, int bt, char d) : _clockTime(ct), _boardTool(bt), _direction(d) {};
	Move() {};
	void set(int ct, int bt, char d) {
		_clockTime = ct;
		_boardTool = bt;
		_direction = d;
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