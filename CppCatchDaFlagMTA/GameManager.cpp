#include "stdafx.h"
#include "GameManager.h"

void GameManager::start(Player pa, Player pb) {
	_b->printBoard(pa,pb);
	char ch = 0;
	Player *playing;
	int i = 0, tool;
	while (1==1) {
		playing = (i % 2 ? &pb : &pa);
		setTextColor(playing->getColor());
		ch = _b->getBoardChar(playing->getName() + " Choose your Game Tool: ");
		tool = ch - '0';

		ch = _b->getBoardChar(("Tool " + string(1, ch)) + " plays, choose your move: ");
		
		playing->moveTool(ch, tool, _b);

		i++;
		
	}

	setTextColor(WHITE);
}
