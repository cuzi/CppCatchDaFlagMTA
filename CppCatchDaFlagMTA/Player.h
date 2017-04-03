#pragma once
#include <iostream>
#include <string>
#include "BoardTool.h"
#include "Board.h"


using namespace std;

class Player {
	BoardTool playerTools[3] ;
	string _name;
	int _color = WHITE;
	int _score;

public:
	Player(Board b, string name, int color) : _name(name), _score(0), _color(color) {
		getRandBoardTools(b);
	}
	
	void setScore(int score) {
		_score = score;
	}
	
	void setName(string name) {
		_name = name;
	}
	
	string getName() {
		return _name;
	}
	
private:

	void getRandBoardTools(Board& b) {
		int i = 0;
		for (auto &tool : playerTools) {
			tool.setChar('A' + i);
			getCellPos(b, tool);
			i++;
		}
	}

	void SaveBoardTools(Board& b) {
		for (auto &tool : playerTools) {
			b.setBoardCell(tool.getX(),tool.getY(),tool.getC());
		}
	}

	void getCellPos(Board& b, BoardTool bt) {
		do {
			bt.set(rand() % 6, rand() % 12);
		} while (!b.isCellEmpty(bt.getX(),bt.getY()));
	}
};