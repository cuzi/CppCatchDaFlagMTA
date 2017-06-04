#pragma once

#include <iostream>
#include <string>
#include "Player.h"

using namespace std;

class ManualPlayer: public Player{

	virtual void setPlayer(int player) {};
	virtual void init(const BoardData& board) {};
	virtual GameMove play(const GameMove& opponentsMove) { return GameMove(0, 0, 0, 0); };

};