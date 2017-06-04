#pragma once

#include <iostream>
#include <string>
#include "AbstractPlayer.h"

using namespace std;

class Player: public AbstractPlayer {
	string _name;
	int _score = 0;

public:
	enum { A = 1, B = 2, C = 3, E = 7, F = 8, G = 9 };

	Player(string name) : _name(name) {};
	
	int getScore() const {
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

	virtual void setPlayer(int player) {};
	virtual void init(const BoardData& board) {};
	virtual GameMove play(const GameMove& opponentsMove) { return GameMove(0, 0, 0, 0); };
	virtual std::string getName() const { return _name; };

};