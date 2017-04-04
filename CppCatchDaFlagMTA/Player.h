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
	int _color = WHITE;
	int _score;

public:
	Player(Board *b, string name, int color);
	
	void setScore(int score) {
		_score = score;
	}

	int getColor() {
		return _color;
	}
	
	void setName(string name) {
		_name = name;
	}
	
	string getName() {
		return _name;
	}
	
private:

	void getRandBoardTools(Board *b);

	void SaveBoardTools(Board *b);

	void getCellPos(Board *b, BoardTool bt);
};