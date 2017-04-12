#include "stdafx.h"
#include "Player.h"


void Player::setToolPos(Board *b, BoardTool *bt) {
	int key;

	switch (_key) {
	case Player::A:
		key = 0;
		break;
	case Player::E:
		key = 8;
		break;
	}

	do {
		bt->set((rand() % (b->getBoardWidth() - 1)) , rand() % 4 + key);
	} while (!b->isCellEmpty(bt->getX(), bt->getY()));
}

void Player::printToolsOnBoard(Board * b) {
	for (auto &tool : playerTools) {
		if (tool.isLive())
			b->printCellByPos(tool.getC(), tool.getX(), tool.getY(), _color);
	}
}
void Player::getRandBoardTools(Board *b,int key) {
	int i = 0;
	for (auto &tool : playerTools) {
		tool.setChar('0' + key + i);
		setToolPos(b, &tool);
		i++;
	}
}

void Player::initPos(Board *b) {
	for (auto &tool : playerTools) {
		setToolPos(b, &tool);
	}
}

Player::Player(Board *b, string name,int key, int color) : _name(name),_key(key), _score(0), _color(color) {
	getRandBoardTools(b, key);
}