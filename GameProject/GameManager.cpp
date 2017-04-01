//#include <Windows.h>
//#include <conio.h>
#include <ncurses.h>
#include <unistd.h>
#include "GameManager.h"

void GameManager::run() {
	// run code is ugly, you should refactor
	char ch = 0;
	starToEat.draw();
	while (ch != ESC) {
		s[0].move();
		if (s[0].isOn(starToEat)) {
			std::cout << "Snake 1 Won!" << endl;
			break;
		}
		else if (s[1].isOn(starToEat)) {
			std::cout << "Snake 2 Won!" << endl;
			break;
		}
		s[1].move();
		//Sleep(80);
        initscr();
        cbreak();
        noecho();
        scrollok(stdscr, TRUE);
        nodelay(stdscr, TRUE);
        
		sleep(10);
		if (_kbhit()) {
			ch = _getch();
			s[0].notifyKeyHit(ch);
			s[1].notifyKeyHit(ch);
		}
	}
}
