#pragma once
#include <iostream>
#include <string>
#include <stack>
#include "stdafx.h"
#include "AbstractPlayer.h"
#include "BoardData.h"
#include "AlgorithmRegisteration.h"

using namespace std;

class AlgorithmPlayer : public AbstractPlayer {
	int playerKey = -1;
	static const int TOOLS_SIZE = 3;
	const int BIG_MOVES = BoardData::cols * BoardData::rows;
	string _name;
	mutable const BoardData* boardInst = nullptr;
	enum {SEA = 'S', FR = 'T', EMPTY};
	int board[BoardData::cols][BoardData::rows]{EMPTY};

	struct PlayerCoordinate {
		int x = -1, y = -1;
		PlayerCoordinate(int _x, int _y) : x(_x), y(_y) {}
		PlayerCoordinate() {}
		void set(int _x, int _y) { 
			x = _x; 
			y = _y; 
		}
		bool operator==(PlayerCoordinate cord) { return cord.x == x && cord.y == y; }
		int distance(int target_x, int target_y) {return abs(x - target_x) + abs(y - target_y);}
		int distance(PlayerCoordinate cord) {return distance(cord.x, cord.y);}
	};

	struct AlgoTool {
		PlayerCoordinate cords;
		enum { BLOCKED_CELL = -10, EMPTY_CELL = 0 };
		enum PRIORIY_CELL { KILLER_CELL = -4, SEA_ELGIBLE = -3, TREE_ELGIBLE = -2, KILL_OPT = -2};
		int pathBoard[BoardData::cols][BoardData::rows]{ EMPTY_CELL };
		stack <PlayerCoordinate> expectedMoves;
		/*
		 * elgLevel: 
		 * 3 - elgible sea and forest
		 * 2 - Elgible forest
		 * 1 - Normal
		 * 0 - Unkown
		 */
		int elgLevel = 0, runCost = -1;
		bool alive = true;

		char type = '#'; // Player type '#' is unkown
		bool operator==(char type) { return this->type == type; }
		bool operator==(PlayerCoordinate cord) { return this->cords == cord; }
		GameMove getAttckNextMove() {
			int pre_x = cords.x, pre_y = cords.y;
			cords = expectedMoves.top();
			expectedMoves.pop();
			return GameMove(pre_x, pre_y, cords.x, cords.y);
		}

	};
	PlayerCoordinate MyFlag, targetFlag;
	AlgoTool myTools[TOOLS_SIZE];
	AlgoTool oppTools[TOOLS_SIZE];

	bool isToolAlive(AlgoTool* tool) {
		return board[tool->cords.x][tool->cords.y] == tool->type;
	}
	void setMyTool(int index, int elg, char type, int x, int y) {
		myTools[index].elgLevel = elg;
		myTools[index].type = type;
		myTools[index].cords = { x, y };
	}

	void setenemy(int x, int y) {
		int i = 0;
		for (; oppTools[i].cords.x != -1; ++i);
		oppTools[i].cords = { x, y };
	}
	bool isCordOnBoard(PlayerCoordinate pos) {
		return isXYOnBoard(pos.x, pos.y);
	}
	bool isXYOnBoard(int x, int y) {
		if (x < 0 || x >= BoardData::cols ||
			y < 0 || y >= BoardData::rows)
			return false;
		return true;
	}

	void setToolBoards(AlgoTool* tool);
	void calcOppWay(AlgoTool* tool);
	GameMove getNextMove();
	GameMove moveAttack();
	void setNextStep(AlgoTool* tool, int x, int y, int level);
	void setAnemiesOnToolsBoards(AlgoTool* tool);
	void setenemyOnToolsBoard(AlgoTool* tool, int x, int y);
	void setKillerWayToolsBoards(AlgoTool* tool);
	void setLeePathOnBoard(AlgoTool* tool);
	void changeBoard(const GameMove& move);
	void setToolBoardBlocks(AlgoTool* tool);
	void calcMoves();
	int getToolsCost(AlgoTool* tools);
	int getExpToolsCost(AlgoTool* tools);
	int getStandardFix();
	int getPosAvilable(AlgoTool* tool, int x, int y, char pre_dir, char next_dir);
	void setToolMovesQueue(AlgoTool* tool, int x, int y, char dir);
	PlayerCoordinate* enemyRounds(int x, int y);

public:
	AlgorithmPlayer() : AbstractPlayer() {};
	virtual void setPlayer(int player) { playerKey = player; };
	virtual string getName() const { return _name; };
	string setName(string name) { _name = name; };
	virtual void init(const BoardData& board);
	virtual GameMove play(const GameMove& opponentsMove);


};
