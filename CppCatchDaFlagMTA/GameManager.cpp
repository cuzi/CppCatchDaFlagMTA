#include <Windows.h>
#include <conio.h>
#include "stdafx.h"
#include "GameManager.h"

void GameManager::run() {
	// run code is ugly, you should refactor
	char ch = 0;
	//starToEat.draw();
	while (ch != ESC) {
		if (1==2) {
			std::cout << "Snake 1 Won!" << endl;
			break;
		}
		else if (1==1) {
			std::cout << "Snake 2 Won!" << endl;
			break;
		}
		Sleep(80);
		if (_kbhit()) {
			ch = _getch();
		}
	}
}
