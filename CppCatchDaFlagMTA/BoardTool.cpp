#include "stdafx.h"
#include "Board.h"
#include "BoardTool.h"

void BoardTool::move(Direction dir, Board *b, int color)
{	
	b->resetCellByPos(_x, _y);
	switch (dir) {
	case Direction::UP:
		_y--;
		break;

	case Direction::DOWN:
		_y++;
		break;

	case Direction::RIGHT:
		_x++;
		break;

	case Direction::LEFT:
		_x--;
		break;
	}


	b->printCellByPos(_c, _x, _y, color);

}
