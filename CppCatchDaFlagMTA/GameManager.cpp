#include "stdafx.h"
#include "GameManager.h"

void GameManager::start(Player* pa, Player* pb) {
	// set vars
	bool gameOn = true;
	char ch = 0;
	int i = 0;

	// init game
	_initGame(pa, pb);

	// set first player
	int playing = (i % 2 ? A_KEY : B_KEY);

	while (gameOn && gameStatus(pa, pb)) {
		playing = (i % 2 ? A_KEY : B_KEY);  // don't move it to the end of the loop!
		
		Sleep(200);

		if (_kbhit()) {
			ch = _getch();
			keyPressed(ch);
		}

		gameOn = !_moveTools(playing);
		i++;

		if (ch == ESC) {
			if (showSubMenu(pa, pb))
				return;
			ch = 0;
		}

	}

	_gameWin(playing == Player::A ? pa : pb);
	
	setTextColor(WHITE);
}


bool GameManager::gameStatus(Player* pa, Player* pb) {
	// TODO check logic in tools positions if there is tools in same position 
	//		need to check who win and return false if some player have no tools
	return true;
}

