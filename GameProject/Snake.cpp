#include "Snake.h"
#include "Direction.h"

void Snake::setKeys(const char * keys)
{
	int i = 0;
	for (char& key : _keys) {
		key = keys[i++];
	}
}

void Snake::move()
{
	// changeDirOccasionally(); // in case we still want some randomness
	_body[tail()].erase();
	_body[tail()] = _body[_head];
	_head = tail();
	_body[_head].move();
	_body[_head].draw();
}

void Snake::notifyKeyHit(char ch)
{
	// maybe can be better...
	if (tolower(ch) == _keys[UP]) {
		setDirection(Direction::UP);
	}
	else if (tolower(ch) == _keys[DOWN]) {
		setDirection(Direction::DOWN);
	}
	else if (tolower(ch) == _keys[LEFT]) {
		setDirection(Direction::LEFT);
	}
	else if (tolower(ch) == _keys[RIGHT]) {
		setDirection(Direction::RIGHT);
	}
	else if (tolower(ch) == _keys[STOP]) {
		stop();
	}
}
