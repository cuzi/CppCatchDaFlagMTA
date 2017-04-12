#include "stdafx.h"
#include "GameManager.h"

void GameManager::start(Player pa, Player pb) {
	// set vars
	bool gameOn = true;
	char ch = 0;
	int i = 0, tool;

	// init game
	pa.initPos(_b);
	pb.initPos(_b);
	_b->printBoard(pa, pb);
	
	// set first player
	Player *playing = (i % 2 ? &pb : &pa);

	while (gameOn) {
		playing = (i % 2 ? &pb : &pa);  // don't move it to the end of the loop!
		setTextColor(playing->getColor());
		ch = _b->getCharFromWriteLine(playing->getName() + " Choose your Game Tool: ");
		tool = ch - '0';

		ch = _b->getCharFromWriteLine(("Tool " + string(1, ch)) + " plays, choose your move: ");
		
		gameOn = !playing->moveTool(ch, tool, _b) && gameStatus(pa, pb);
		i++;
	}
	playing->win();

	setTextColor(WHITE);
}

bool GameManager::gameStatus(Player pa, Player pb) {
	// TODO check logic in tools positions if there is tools in same position 
	//		need to check who win and return false if some player have no tools
	return true;
}