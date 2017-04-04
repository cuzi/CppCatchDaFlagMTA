#include "Player.h"

void Player::saveBoardTools(Board *b) {

	for (auto &tool : playerTools) {
		cout << tool.getC() << endl;
		b->setBoardCell(tool.getX(), tool.getY(), tool.getC());
	}
}

void Player::getCellPos(Board *b, BoardTool *bt) {
	do {
		bt->set(rand() % 6, rand() % 12);
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