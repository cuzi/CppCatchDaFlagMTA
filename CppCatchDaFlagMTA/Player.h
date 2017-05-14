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

};