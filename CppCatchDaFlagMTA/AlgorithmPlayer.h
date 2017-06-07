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
		for (int i = 0;i < board.rows;i++) {
			for (int j = 0;j < board.cols;j++) {
				const char c = board.charAt[i][j];
			}
			cout << " ! " << endl;
		}
		cout << "FFFFFFFFFFF";
	};
	virtual GameMove play(const GameMove& opponentsMove) { return GameMove(0, 0, 0, 0); };

};