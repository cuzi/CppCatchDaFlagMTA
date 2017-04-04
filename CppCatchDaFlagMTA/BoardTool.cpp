#include "BoardTool.h"

void BoardTool::move()
{		
	_x = _x + _dir_x;
	_y = _y + _dir_y;
	if (_x < MIN_X) {
		_x = MAX_X;
	}
	else if (_x > MAX_X) {
		_x = MIN_X;
	}
	if (_y < MIN_Y) {
		_y = MAX_Y;
	}
	else if (_y > MAX_Y) {
		_y = MIN_Y;
	}
}
