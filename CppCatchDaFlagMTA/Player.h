#pragma once

#include <iostream>
#include <string>
#include "BoardTool.h"
#include "Board.h"

using namespace std;

class Board;

class Player {
	BoardTool playerTools[3] ;
	string _name;
	int _key;
	int _color = WHITE;
	int _score;

public:
	enum { A = 5, B = 6, C = 7, E = 8, F = 9, G = 10 };

	Player(Board *b, string name,int key, int color);
	
	void setScore(int score) {
		_score = score;
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
	
	string getName() {
		return _name;
	}
	
private:

	void getRandBoardTools(Board *b, int key);

	void saveBoardTools(Board *b);

	void getCellPos(Board *b, BoardTool *bt);
};