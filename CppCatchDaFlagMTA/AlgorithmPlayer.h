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
		for (int i = 0;i < 13;i++) {
			for (int j = 0;j < 13;j++) {
				cout << board.charAt(i, j);
			}
			cout << endl;
		}
	};
	virtual GameMove play(const GameMove& opponentsMove) { return GameMove(0, 0, 0, 0); };

};