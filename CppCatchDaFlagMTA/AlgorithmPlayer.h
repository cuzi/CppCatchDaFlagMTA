#pragma once
#include <iostream>
#include <string>
#include "Player.h"
#include "BoardData.h"

using namespace std;

class AlgorithmPlayer : public Player {
	int playerKey = -1;

public:
	AlgorithmPlayer(string name) : Player(name) {};
	virtual void setPlayer(int player) { playerKey = player; };
	virtual void init(const BoardData& board) {
		
	};
	virtual GameMove play(const GameMove& opponentsMove) { return GameMove(0, 0, 0, 0); };

};