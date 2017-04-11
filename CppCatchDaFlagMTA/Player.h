#pragma once

#include <iostream>
#include <string>
#include "BoardTool.h"
#include "Board.h"
#include "Direction.h"

using namespace std;

class Board;

class Player {

	static const int TOOLS_COUNT = 3;
	BoardTool playerTools[TOOLS_COUNT];
	string _name;
	int _key;
	int _color = WHITE;
	int _score = 0;

public:
	enum { A = 1, B = 2, C = 3, E = 7, F = 8, G = 9 };

	Player(Board *b, string name,int key, int color);
	
	void setScore(int score) {
		_score = score;
	}

	int getScore() {
		return _score;
	}

	int getColor() {
		return _color;
	}
	
	int getKey() {
		return _key;
	}

	void setName(string name) {
		_name = name;
	}

	void printToolsOnBoard(Board * b);

	void moveTool(char dir, int tool, Board *b) {
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

		bt.move(d, b, _color);
	}
	
	string getName() {
		return _name;
	}
	void initPos(Board *b);
private:
	Direction getDirE(Direction_E dir) {
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
			return Direction::RIGHT;
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
			return Direction::RIGHT;
		}
	}
	void getRandBoardTools(Board *b, int key);

	void saveBoardTools(Board *b);

	void setToolPos(Board *b, BoardTool *bt);
};