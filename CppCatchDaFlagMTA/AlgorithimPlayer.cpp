#include "stdafx.h"
#include "AlgorithmPlayer.h"
#include <map>
#include <string>

GameMove AlgorithmPlayer::play(const GameMove& opponentsMove) {
	if (opponentsMove.from_x != opponentsMove.to_x ||
		opponentsMove.from_y != opponentsMove.to_y)
		changeBoard(opponentsMove);
	
	return getNextMove();

}

void AlgorithmPlayer::changeBoard(const GameMove& move) {
	PlayerCoordinate toMove{ move.to_x, move.to_y };
	PlayerCoordinate fromMove{ move.to_x, move.to_y };

	for (int i = 0; i < TOOLS_SIZE; ++i) {
		if ('#' == boardInst->charAt(toMove.x, toMove.y)) {
			if (oppTools[i] == fromMove)
				oppTools[i].cords.set(toMove);
			if (myTools[i] == toMove)
				myTools[i].alive = false;
		}
		else {
			if (oppTools[i] == fromMove)
				oppTools[i].alive = false;

		}

	}


}
int AlgorithmPlayer::getStandardFix() {
	return ((getExpToolsCost(myTools) - getToolsCost(myTools)) / 2);
}
int AlgorithmPlayer::getToolsCost(AlgoTool* tools) {
	int lowestRun = tools[0].alive ? tools[0].runCost : BIG_MOVES;
	for (int i = 1; i < TOOLS_SIZE; ++i)
		if (tools[i].runCost < lowestRun && tools[i].alive)
			lowestRun = tools[i].runCost;

	return lowestRun;
}
int AlgorithmPlayer::getExpToolsCost(AlgoTool* tools) {
	int lowestRun = tools[0].alive ? tools[0].runCost : AlgoTool::BLOCKED_CELL;
	for (int i = 1; i < TOOLS_SIZE; ++i)
		if (tools[i].runCost > lowestRun && tools[i].alive)
			lowestRun = tools[i].runCost;

	return lowestRun;
}
AlgorithmPlayer::PlayerCoordinate AlgorithmPlayer::getOppRunnerCords() {

	AlgoTool* runner = &oppTools[0];

	for (int i = 1; i < TOOLS_SIZE; ++i)
		if (oppTools[i].runCost < runner->runCost || !runner->alive)
			runner = &oppTools[i];

	return runner->cords;
}
void AlgorithmPlayer::setDefend() {
	PlayerCoordinate oppRunner = getOppRunnerCords();

	for (int i = 1; i < TOOLS_SIZE; ++i)
		setToolBoardsToTarget(&myTools[i],oppRunner, false);

}
GameMove AlgorithmPlayer::moveAttack() {
	AlgoTool* runner = &myTools[0];

	for (int i = 1; i < TOOLS_SIZE; ++i)
		if (myTools[i].runCost < runner->runCost || !runner->alive)
			runner = &myTools[i];

	return runner->getAttckNextMove();
}
GameMove AlgorithmPlayer::getNextMove() {
	calcMoves();

	//if (getToolsCost(myTools) > getToolsCost(oppTools) ) setDefend();

	return moveAttack();

}

void AlgorithmPlayer::init(const BoardData& board) {
	char c;
	this->boardInst = &board;
	for (int j = 0; j < board.cols; ++j) {
		for (int i = 0; i < board.rows; ++i) {
			c = board.charAt(j, i);
			switch (c) {
			case '#':
				setenemy(i, j);
				break;
			case 'A':
				(playerKey == 1 ? MyFlag : targetFlag).x = i;
				(playerKey == 1 ? MyFlag : targetFlag).y = j;
				break;
			case 'B':
				(playerKey == 2 ? MyFlag : targetFlag).x = i;
				(playerKey == 2 ? MyFlag : targetFlag).y = j;
				break;
			case SEA:
			case FR:
				this->board[i][j] = c;
				break;
			case '1':
			case '7':
				setMyTool(0, 1, c, i, j);
				break;
			case '2':
			case '8':
				setMyTool(1, 2, c, i, j);
				break;
			case '3':
			case '9':
				setMyTool(2, 3, c, i, j);
				break;
			}
		}
	}

};

void AlgorithmPlayer::calcMoves() {

	for (int i = 0; i < TOOLS_SIZE; ++i) {
		if (myTools[i].alive) {
			setToolBoards(&(myTools[i]));
		}
		if (oppTools[i].alive)
			calcOppWay(&(oppTools[i]));
	}
}

void AlgorithmPlayer::calcOppWay(AlgoTool* tool) {
	tool->runCost = tool->cords.distance(MyFlag);
}
void AlgorithmPlayer::setToolBoards(AlgoTool* tool) {
	setToolBoardsToTarget(tool, targetFlag, true);
}
void AlgorithmPlayer::setToolBoardsToTarget(AlgoTool* tool, PlayerCoordinate target, bool considerOppTools) {
	/* tool is the index 0-2 */
	setToolBoardBlocks(tool);
	if (considerOppTools)
		setAnemiesOnToolsBoards(tool);
	setLeePathOnBoard(tool, target);
	// TODO: Optional set killer cordinates for each tool
}

void AlgorithmPlayer::setToolBoardBlocks(AlgoTool* tool) {
	// set tool uneligible ways on path board
	for (int i = 0; i < BoardData::cols; ++i) {
		for (int j = 0; j < BoardData::rows; ++j) {
			if (board[i][j] == SEA)
				tool->pathBoard[i][j] = (tool->elgLevel != 3) ? AlgoTool::BLOCKED_CELL : AlgoTool::EMPTY_CELL;
			else if (board[i][j] == FR)
				tool->pathBoard[i][j] = !(tool->elgLevel == 3 || tool->elgLevel == 2) ? AlgoTool::BLOCKED_CELL : AlgoTool::EMPTY_CELL;
		}
	}
}


void AlgorithmPlayer::setLeePathOnBoard(AlgoTool* tool, PlayerCoordinate target) {
	int x = tool->cords.x, y = tool->cords.y;
	tool->pathBoard[x][y] = 1;
	setNextStepLeeAlgo(tool, x - 1, y, 1, target);
	setNextStepLeeAlgo(tool, x + 1, y, 1, target);
	setNextStepLeeAlgo(tool, x, y - 1, 1, target);
	setNextStepLeeAlgo(tool, x, y + 1, 1, target);

	tool->clearMoves();
	setToolMovesQueue(tool, target.x, target.y, '\0');

	tool->runCost = tool->expectedMoves.size();
}

int AlgorithmPlayer::getPosAvilable(AlgoTool* tool, int x, int y, char pre_dir, char next_dir) {
	return isXYOnBoard(x, y) && pre_dir != next_dir && tool->pathBoard[x][y] != AlgoTool::BLOCKED_CELL ? tool->pathBoard[x][y] : BIG_MOVES;
}
void AlgorithmPlayer::setToolMovesQueue(AlgoTool* tool, int x, int y, char dir) {

	if (x == tool->cords.x && y == tool->cords.y)
		return;

	tool->runCost += 1;
	tool->expectedMoves.push({x , y});


	int up = getPosAvilable(tool, x, y + 1, dir, 'u'),
		down = getPosAvilable(tool, x, y - 1, dir, 'd') ,
		right = getPosAvilable(tool, x - 1, y, dir, 'r'),
		left = getPosAvilable(tool, x + 1, y, dir, 'l');

	if (up < down && up < right && up < left && up != BIG_MOVES)
		setToolMovesQueue(tool, x, y + 1, 'd');
	else if (down < right && down < left && down != BIG_MOVES)
		setToolMovesQueue(tool, x, y - 1, 'u');
	else if (right < left && right != BIG_MOVES)
		setToolMovesQueue(tool, x - 1, y, 'l');
	else if (left != BIG_MOVES) setToolMovesQueue(tool, x + 1, y, 'r');

}

void AlgorithmPlayer::setNextStepLeeAlgo(AlgoTool* tool, int x, int y, int preLevel, PlayerCoordinate target) {
	if (!isXYOnBoard(x, y) || tool->pathBoard[x][y] == AlgoTool::BLOCKED_CELL 
		|| (tool->pathBoard[x][y] < preLevel && tool->pathBoard[x][y] != AlgoTool::EMPTY_CELL) 
		|| (x == target.x && y == target.y))
		return;
	++preLevel;

	tool->pathBoard[x][y] = preLevel;

	setNextStepLeeAlgo(tool, x - 1, y, preLevel,target);
	setNextStepLeeAlgo(tool, x + 1, y, preLevel,target);
	setNextStepLeeAlgo(tool, x, y - 1, preLevel,target);
	setNextStepLeeAlgo(tool, x, y + 1, preLevel,target);

}

void AlgorithmPlayer::setAnemiesOnToolsBoards(AlgoTool* tool) {
	for (int i = 0; i < TOOLS_SIZE; ++i) {
		setenemyOnToolsBoard(tool, oppTools[i].cords.x, oppTools[i].cords.y);
	}
}

void AlgorithmPlayer::setKillerWayToolsBoards(AlgoTool* tool) {
	// TODO: Optional
}


void AlgorithmPlayer::setenemyOnToolsBoard(AlgoTool* tool, int x, int y) {
	PlayerCoordinate* cords = enemyRounds(x, y);
	for (int i = 0 ; i < 5; ++i)
	{
		if (isCordOnBoard(cords[i]))
			tool->pathBoard[cords[i].x][cords[i].y] = AlgoTool::BLOCKED_CELL;
	}
	delete[] cords;
}


AlgorithmPlayer::PlayerCoordinate* AlgorithmPlayer::enemyRounds(int x, int y) {
	PlayerCoordinate *cords = new PlayerCoordinate[5];

	cords[0].set(x, y);
	cords[1].set(x, y - 1);
	cords[2].set(x, y + 1);
	cords[3].set(x - 1, y);
	cords[4].set(x + 1, y);

	return cords;

}
