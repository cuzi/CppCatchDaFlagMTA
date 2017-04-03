#pragma once

#include <iostream>
#include "Utils.h"
#include "Direction.h"

using namespace std;

class BoardTool {
	enum { MIN_X = 0, MAX_X = 79, MIN_Y = 0, MAX_Y = 24 };
	int _x = 10, _y = 10;
	char _c = '*';
	int _dir_x = 1, _dir_y = 0;

public:
	BoardTool() {}
	
	BoardTool(int x, int y, char ch = '*') : _x(x), _y(y), _c(ch) {}
	
	bool operator==(const BoardTool& p) {
		return _x == p._x && _y == p._y;
	}
	
	void set(int x, int y, int dir_x = 1, int dir_y = 0) {
		_x = x;
		_y = y;
		_dir_x = dir_x;
		_dir_y = dir_y;
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
	
	void move();
	
	
	void setDirection(Direction d) {
		switch (d) {
		case Direction::UP:
			_dir_x = 0;
			_dir_y = -1;
			break;
		case Direction::DOWN:
			_dir_x = 0;
			_dir_y = 1;
			break;
		case Direction::LEFT:
			_dir_x = -1;
			_dir_y = 0;
			break;
		case Direction::RIGHT:
			_dir_x = 1;
			_dir_y = 0;
			break;
		}
	}
	
	void stop() {
		_dir_x = 0;
		_dir_y = 0;
	}
	
	void changeDir() {
		int dir = rand() % 4;
		setDirection((Direction)dir);
	}

private:
	void draw(char c) {
		gotoxy(_x, _y);
		cout << c;
		// make sure it gets to screen on time
		cout.flush();
	}
};
