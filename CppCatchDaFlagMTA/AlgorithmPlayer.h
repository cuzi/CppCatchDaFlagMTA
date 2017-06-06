#pragma once
#include <iostream>
#include <string>
#include "Player.h"
#include "AlgoBoardData.h"
#include "BoardTool.h"

using namespace std;

class AlgorithmPlayer : public Player {
	int playerKey = -1;
	BoardData& const abd;
	BoardTool* & const tools;

	virtual void setPlayer(int player) { playerKey = player; };
	void setTools(BoardTool* bt) { tools = bt; };
	virtual void init(const BoardData& board) {
		abd = board;
	};
	virtual GameMove play(const GameMove& opponentsMove) { return GameMove(0, 0, 0, 0); };

};