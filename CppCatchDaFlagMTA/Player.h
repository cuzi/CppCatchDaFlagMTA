#pragma once

#include <iostream>
#include <string>
#include "BoardTool.h"
#include "Board.h"
#include "Direction.h"

using namespace std;

class Board;

class Player {
	string _name;
	int _score = 0;

public:
	enum { A = 1, B = 2, C = 3, E = 7, F = 8, G = 9 };

	Player(string name) : _name(name) {};
	
	int getScore() {
		return _score;
	}

	void resetScore() {
		_score = 0;
	}

	void win() {
		++_score;
	}
		

	void setName(string name) { 
		_name = name;
	}

	string getName() {
		return _name;
	}
/*	void printToolsOnBoard(Board* b);

	// if flag catched return true
	bool moveTool(int tool, Board *b) {

		BoardTool bt;
		switch (_key) {
		case E:
			bt = playerTools[tool - E];
			break;
		case A:
			bt = playerTools[tool - A];
			break;
		}

		return bt.move(b, _color);
	}
	void changeToolDir(char dir, int tool) {
		Direction d;
		BoardTool bt;

		switch (_key) {
		case E:
			d = getDirE((Direction_E)dir);
			bt = playerTools[tool - E];
			break;
		case A:
			d = getDirA((Direction_A)dir);
			bt = playerTools[tool - A];
			break;
		}
		if (d != Direction::NONE)
		bt.setDirection(d);
	}
	
	void initPos(Board *b);*/
private:
	/*Direction getDirE(Direction_E dir) {
		switch (dir) {
		case Direction_E::UP:
			return Direction::UP;
		case Direction_E::DOWN:
			return Direction::DOWN;
		case Direction_E::LEFT:
			return Direction::LEFT;
		case Direction_E::RIGHT:
			return Direction::RIGHT;
		default: // TODO: Change it to NULL
			return Direction::NONE;
		}
	}
	Direction getDirA(Direction_A dir) {
		switch (dir) {
		case Direction_A::UP:
			return Direction::UP;
		case Direction_A::DOWN:
			return Direction::DOWN;
		case Direction_A::LEFT:
			return Direction::LEFT;
		case Direction_A::RIGHT:
			return Direction::RIGHT;
		default: // TODO: Change it to NULL
			return Direction::NONE;
		}
	}
	void getRandBoardTools(Board *b, int key);

	void saveBoardTools(Board *b);

	void setToolPos(Board *b, BoardTool *bt);*/
	
};