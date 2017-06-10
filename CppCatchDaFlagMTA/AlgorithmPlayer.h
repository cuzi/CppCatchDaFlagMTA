#pragma once
#include <iostream>
#include <string>
#include "Player.h"
#include "BoardData.h"

using namespace std;

class AlgorithmPlayer : public Player {
	int playerKey = -1;
	static const int TOOLS_SIZE = 3;
	enum {SEA = 'S', FR = 'T', EMPTY};
	int board[BoardData::cols][BoardData::rows]{EMPTY};

	struct PlayerCoordinate {
		int x = -1, y = -1;
	};

	struct AlgoTool {
		PlayerCoordinate cords;
		/*
		 * elgLevel: 
		 * 3 - elgible sea and forest
		 * 2 - Elgible sea
		 * 1 - Normal
		 * 0 - Unkown
		 */
		int elgLevel = 0, runCost = -1;

		char type = '#'; // Player type '#' is unkown
	};
	PlayerCoordinate MyFlag, targetFlag;
	AlgoTool myTools[TOOLS_SIZE];
	AlgoTool oppTools[TOOLS_SIZE];

	void setMyTool(int index, int elg, char type, int x, int y) {
		myTools[index].elgLevel = elg;
		myTools[index].type = type;
		myTools[index].cords.x = x;
		myTools[index].cords.y = y;
	}

	void setAnemy(int x, int y) {
		int i = 0;
		for (; oppTools[i].cords.x == -1; ++i);
		oppTools[i].cords.x = x;
		oppTools[i].cords.y = y;
	}

public:
	AlgorithmPlayer(string name) : Player(name) {};
	virtual void setPlayer(int player) { playerKey = player; };
	virtual void init(const BoardData& board);
	virtual GameMove play(const GameMove& opponentsMove);

};