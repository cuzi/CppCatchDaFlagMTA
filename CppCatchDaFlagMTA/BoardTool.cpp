#include "stdafx.h"
#include "Board.h"
#include "BoardTool.h"

// return true only when winning
bool BoardTool::move(Board *b)
{	
	signed int x = _x + _dir_x, y = _y + _dir_y, catched;

	if ( isElgibleToPos(x, y, b) && _isLive) {
		b->resetCellByPos(_x, _y);
		_x = x;
		_y = y;

		cout.flush();
		b->printCellByPos(_c, _x, _y, _color);

		catched = b->GetCell(_x, _y);

		return (catched == Board::FlgA || catched == Board::FlgB);
	}
	else {
		stop();
	}
	return false;
}

bool BoardTool::isElgibleToPos(int x, int y, Board *b) {
	// TODO: need to validate that there is no other player on position

	if (x < 0 || x >= b->getBoardWidth())
		return false;
	if (y < 0 || y >= b->getBoardHeigth())
		return false;

	int newPosContent = b->GetCell(x, y);

	switch (newPosContent) {
	case Board::FR:
		switch (_c - '0')
		{
		case Board::A:
		case Board::C:
		case Board::G:
			return false;
		}
		break;
	case Board::SEA:
		switch (_c - '0')
		{
		case Board::A:
		case Board::F:
		case Board::G:
			return false;
		}
		break;
	case Board::FlgA:
		switch (_c - '0')
		{
		case Board::A:
		case Board::B:
		case Board::C:
			return false;
		}
		break;
	case Board::FlgB:
		switch (_c - '0')
		{
		case Board::E:
		case Board::F:
		case Board::G:
			return false;
		}
		break;

	}

	return true;
}
