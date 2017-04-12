#pragma once

#include "stdafx.h"
#include "Utils.h"
#include "Direction.h"

using namespace std;

class Board;

class BoardTool {
	int _x = 10, _y = 10;
	char _c = '*';
	bool _isLive = true;

public:
	BoardTool() {}
	
	BoardTool(int x, int y, char ch = '*',bool isLive = true) : _x(x), _y(y), _c(ch), _isLive(isLive) {}
	
	bool operator==(const BoardTool& p) {
		return _x == p._x && _y == p._y;
	}
	bool isLive() {
		return _isLive;
	}
	void die() {
		_isLive = false;
	}
	void set(int x, int y) {
		_x = x;
		_y = y;
	}
	
	int getX() {
		return _x;
	}

	char getC() {
		return _c;
	}

	int getY() {
		return _y;
	}
	void setChar(char c) {
		_c = c;
	}
	
	void draw() {
		draw(_c);
	}
	
	void erase() {
		draw(' ');
	}
	
	bool move(Direction dir, Board *b, int color);
	
private:
	void draw(char c) {
		gotoxy(_x, _y);
		cout << c;
		// make sure it gets to screen on time
		cout.flush();
	}
	bool isElgibleToPos(int x, int y, Board* b);
};
