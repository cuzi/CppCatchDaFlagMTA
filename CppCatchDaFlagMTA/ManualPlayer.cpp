#include "ManualPlayer.h"

void ManualPlayer::keyPressed(char c) {
	switch (c)
	{
	case '0' + Board::A:
	case '0' + Board::B:
	case '0' + Board::C:
		break;
	case '0' + Board::E:
	case '0' + Board::F:
	case '0' + Board::G:
		break;

	default:
		_changeDir(c);
		break;
	}
}
