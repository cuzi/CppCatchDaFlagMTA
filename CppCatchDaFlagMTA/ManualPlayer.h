#pragma once

#include <iostream>
#include <string>
#include "Player.h"
#include <conio.h>
#include "Board.h"
#include "Direction.h"

using namespace std;

class ManualPlayer: public Player{

	int selectedA = -1, selectedB = -1;

	virtual void setPlayer(int player) {};
	virtual void init(const BoardData& board) {};
	virtual GameMove play(const GameMove& opponentsMove);
	void keyPressed(char c);
};