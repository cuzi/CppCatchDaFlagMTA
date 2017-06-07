#pragma once
#include "BoardData.h"
#include "Board.h"

class BoardTool;
class Board;

class AlgoBoardData : public BoardData {
	int ** const _gameBoard;
	BoardTool* const btPa;
	BoardTool* const btPb;
	int _playerKey;

public:
	AlgoBoardData(int ** const b, BoardTool* const bta, BoardTool* const btb, int key) : _gameBoard(b), btPa(bta), btPb(btb), _playerKey(key) {};
	virtual char charAt(int x, int y) const {
		int cell = _gameBoard[x][y];

		switch (cell) {
		case Board::A:
		case Board::B:
		case Board::C:
			return (_playerKey == 1) ? cell - '0' : '#';
		case Board::E:
		case Board::F:
		case Board::G:
			return (_playerKey == 2) ? cell - '0' : '#';
		default:
			return cell - '0';

		}
	};
};