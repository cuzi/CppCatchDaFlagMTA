#pragma once

#include "stdafx.h"
#include "Utils.h"
#include "Direction.h"
#include "GameManager.h"

using namespace std;

class Board;
class GameManager;

class BoardTool {
	int _x = 10, _y = 10, _dir_x = 0, _dir_y = 0;
	char _c = '*';
	bool _isLive = false;
	int _color = WHITE;

public:
	BoardTool() {}
	BoardTool(int x, int y, char ch = '*',int color = WHITE) : _x(x), _y(y), _c(ch), _color(color) {}
	
	bool move(Board *b, GameManager *gm, bool print);
	bool isElgibleToPos(int x, int y, Board* b, GameManager *gm);

	bool operator==(const BoardTool& p) {
		return _x == p._x && _y == p._y;
	}

	void init() {
		stop();
		_isLive = true;
	}
	bool isLive() {
		return _isLive;
	}
	bool isOnPos(int x, int y) {
		return  _isLive && x == _x && y == _y;
	}
	void die() {
		_isLive = false;
	}
	void set(int x, int y) {
		_x = x;
		_y = y;
	}
	bool isMoving() {
		return (_dir_x != 0 || _dir_y != 0);
	}
	int getX() {
		return _x;
	}
	char getC() {
		return _c;
	}
	int getColor() {
		return _color;
	}
	void setColor(int color) {
		_color = color;;
	}
	int getY() {
		return _y;
	}
	void setChar(char c) {
		_c = c;
	}
	void stop() {
		_dir_x = 0;
		_dir_y = 0;
	}
	bool setDirection(Direction d) {
		switch (d) {
		case Direction::UP:
			_dir_x = -1;
			_dir_y = 0;
			break;
		case Direction::DOWN:
			_dir_x = 1;
			_dir_y = 0;
			break;
		case Direction::LEFT:
			_dir_x = 0;
			_dir_y = -1;
			break;
		case Direction::RIGHT:
			_dir_x = 0;
			_dir_y = 1;
			break;
		default:
			return false;
		}

		return true;
	}

private:
	void draw(char c) {
		gotoxy(_x, _y);
		cout << c;
		// make sure it gets to screen on time
		cout.flush();
	}
};
