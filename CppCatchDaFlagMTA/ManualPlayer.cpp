#include "ManualPlayer.h"

void ManualPlayer::keyPressed(char c) {
	switch (c)
	{
	case '0' + Board::A:
	case '0' + Board::B:
	case '0' + Board::C:
		selectedA = c - '1';
		break;
	case '0' + Board::E:
	case '0' + Board::F:
	case '0' + Board::G:
		selectedB = c - Board::E - '0';
		break;

	default:
		break;
	}
}
GameMove ManualPlayer::play(const GameMove& opponentsMove) {
	if (_kbhit()) {
		char ch = _getch();
		keyPressed(ch);
		return futilityMove;
	}
	else {
		return futilityMove;
	}
};