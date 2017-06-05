#pragma once

#include <iostream>
#include <string>
#include "Player.h"
#include <conio.h>
#include "Board.h"
#include "Direction.h"

using namespace std;

class ManualPlayer: public Player{

	virtual void setPlayer(int player) {};
	virtual void init(const BoardData& board) {};
	virtual GameMove play(const GameMove& opponentsMove) { 
		if (_kbhit()) {
			char ch = _getch();
			keyPressed(ch);
		}
		return futilityMove; };
	void keyPressed(char c);
};