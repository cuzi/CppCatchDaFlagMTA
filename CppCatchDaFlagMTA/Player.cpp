#include "stdafx.h"
#include "Player.h"

void Player::saveBoardTools(Board *b) {

	for (auto &tool : playerTools) {
		b->setBoardCell(tool.getX(), tool.getY(), tool.getC());
	}
}

void Player::getCellPos(Board *b, BoardTool *bt) {
	int key = getKey();

	switch (key) {

	case Player::A:
		key = 0;
		break;
	case Player::E:
		key = 8;
		break;
	}

	do {
		bt->set(rand() % 5 + key, rand() % 12);
	} while (!b->isCellEmpty(bt->getX(), bt->getY()));
}

void Player::getRandBoardTools(Board *b,int key) {
	int i = 0;
	for (auto &tool : playerTools) {
		tool.setChar(key + i);
		getCellPos(b, &tool);
		i++;
	}
}

Player::Player(Board *b, string name,int key, int color) : _name(name),_key(key), _score(0), _color(color) {
	getRandBoardTools(b, key);
	saveBoardTools(b);
}