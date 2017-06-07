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

public:
	AlgorithmPlayer(std::string name) { Player(name); };
	virtual void setPlayer(int player) { playerKey = player; };
	virtual void init(const BoardData& board) {
		abd = board;
		for (int i = 0;i < abd.rows;i++) {
			for (int j = 0;j < abd.cols;j++) {
				cout << abd.charAt[i][j];
			}
			cout << " ! " << endl;
		}
		cout << "FFFFFFFFFFF";
	};
	virtual GameMove play(const GameMove& opponentsMove) { return GameMove(0, 0, 0, 0); };

};