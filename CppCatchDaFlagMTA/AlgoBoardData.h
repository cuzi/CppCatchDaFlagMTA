#pragma once
#include "BoardData.h"

class AlgoBoardData : public BoardData {
	int ** const _gameBoard;

public:
	AlgoBoardData(int ** const b) : _gameBoard(b) {};
	virtual char charAt(int x, int y) const {  
		return _gameBoard[x][y];
	};
};