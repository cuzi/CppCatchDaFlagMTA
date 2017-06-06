#pragma once
#include "BoardData.h"
#include "Board.h"
#include "BoardTool.h"

class AlgoBoardData : public BoardData {
	int ** const _gameBoard;
	BoardTool* const btPa;
	BoardTool* const btPb;

public:
	AlgoBoardData(int ** const b, BoardTool* const bta, BoardTool* const btb) : _gameBoard(b), btPa(bta), btPb(btb) {};
	virtual char charAt(int x, int y) const {
		int cell = _gameBoard[x][y];

		switch (cell) {
		case Board::A:
		case Board::B:
		case Board::C:
			return cell - '0';
		default:
			return cell - '0';

		}
	};
};