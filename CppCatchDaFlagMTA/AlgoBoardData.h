#pragma once
#include "BoardData.h"
#include "BoardTool.h"
#include "Board.h"

class BoardTool;

class AlgoBoardData : public BoardData {
	int ** const _gameBoard;
	BoardTool* const btPa;
	BoardTool* const btPb;
	int _playerKey;

	const int TOOLS_COUNT = 3;

	int searchInTools(int x, int y) const;

public:
	AlgoBoardData(int ** const b, BoardTool* const bta, BoardTool* const btb, int key) : _gameBoard(b), btPa(bta), btPb(btb), _playerKey(key) {};
	virtual char charAt(int x, int y) const {
		int cell = searchInTools(x, y);
		cell = (cell != -1) ? cell : _gameBoard[x][y];
		switch (cell) {
		case Board::A:
		case Board::B:
		case Board::C:
			return (_playerKey == 1) ? Board::getBoardChar(cell) : '#';
		case Board::E:
		case Board::F:
		case Board::G:
			return (_playerKey == 2) ? Board::getBoardChar(cell) : '#';
		default:
			return Board::getBoardChar(cell);

		}
	};
	
};