#include "stdafx.h"
#include "Board.h"
#include "BoardTool.h"
#include "GameManager.h"

// return true only when winning
bool BoardTool::move(Board *b, GameManager *gm)
{	
	signed int x = _x + _dir_x, y = _y + _dir_y, catched;
	if (_dir_y != 0 || _dir_x != 0) {
		if (isElgibleToPos(x, y, b, gm) && _isLive) {
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
			if (!_isLive) {
				b->resetCellByPos(_x, _y);
			}
		}
	}
	return false;
}

bool BoardTool::isElgibleToPos(int x, int y, Board *b, GameManager *gm) {
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
	if (gm->isAnyToolInPos(x, y)) {
		BoardTool* bt = gm->getToolInPos(x, y);

		if (gm->isFriends(this, bt) && bt->getC() != _c) {
			return false;
		}

		gm->fight(this, bt);

	}

	return true;
}
