#pragma once

#include <Windows.h>
#include <conio.h>
#include "stdafx.h"
#include "Board.h"
#include "BoardTool.h"

class GameManager {
	enum { RESUME = 1, RESTART = 2, MAIN_MENU = 8, EXIT = 9 };
	char* txt[9] = { "Resume", "Restart Game", "", "","","","","Main Menu", "Exit Game" };

	static const int TOOLS_COUNT = 3;

	BoardTool ATools[TOOLS_COUNT];
	BoardTool BTools[TOOLS_COUNT];

	int aColor = BLUE;
	int bColor = RED;

	static const int A_KEY = Player::A;
	static const int B_KEY = Player::E;

	int selectedA = -1, selectedB = -1;


	enum { ESC = 27 };

	Board* _b;

public:
	GameManager(Board * b) : _b(b) {}
	void start(Player* pa, Player *pb);
private:
	bool gameStatus(Player* pa, Player* pb);

	// If submenu return true the game need to be stopped
	bool showSubMenu(Player* pa, Player* pb) {
		int i;

		_printSubMenu();

		cin >> i;

		switch (i) {
		case RESUME:
			_b->printBoard(pa,aColor,pb,bColor);
			printToolsOnBoard();
			return false;
			break;
		case RESTART:
			start(pa, pb);
			return true;
			break;
		case MAIN_MENU:
			return true;
			break;
		case EXIT:
			_b->cleanBoard();
			cout << "bye bye";
			Sleep(500);
			exit(0);
			break;
		default:
			return showSubMenu(pa, pb);
		}
	}

	void _printLine(int i) {
		if (txt[i] != "") {
			cout << "  " << (i + 1) << " - " << txt[i] << endl;
		}
	}

	void _printSubMenu() {
		_b->cleanBoard();
		cout << "Game Stopped\n";
		cout << "Choose from the following:\n";
		for (int i = 0; i < EXIT; ++i) {
			_printLine(i);
		}
	}


	void _setTools(BoardTool* playerTools, int color, int key ) {

		for (int i = 0; i < TOOLS_COUNT; ++i) {
			playerTools[i].setColor(color);
			playerTools[i].setChar('0' + i + key);
			_setToolPos(_b, &playerTools[i], key);
			playerTools[i].init();
		}
	}

	BoardTool *_getTools(int key) {
		return (key == A_KEY ? ATools : BTools);
	}

	bool _moveTools(int key ) {
		bool win = false;
		for (int i = 0; i < TOOLS_COUNT; ++i) {
			win = win || (_getTools(key))[i].move(_b);
		}

		return win;
	}
	void _gameWin(Player *p) {
		_b->cleanBoard();
		p->win();
		_printGameOver();
		cout << p->getName() << " Won the game!\n";
		_playWinSound();
		Sleep(1250);
	}

	void _printGameOver() {
		cout << "\n  ___    __    __  __  ____    _____  _  _  ____  ____ \n";
		cout << " / __)  /__\\  (  \\/  )( ___)  (  _  )( \\/ )( ___)(  _ \\\n";
		cout << "( (_-. /(__)\\  )    (  )__)    )(_)(  \\  /  )__)  )   /\n";
		cout << " \\___/(__)(__)(_/\\/\\_)(____)  (_____)  \\/  (____)(_)\\_)\n\n";
	}

	void _playWinSound() {
		Beep(2060, 400);
		Beep(2060, 400);
		Beep(2183, 1000);
		Beep(3087, 400);
		Beep(2183, 1200);
	}

	void _setToolPos(Board *b, BoardTool *bt, int key) {
		int _key = 0, x, y;
		switch (key) {
		case A_KEY:
			_key = 0;
			break;
		case B_KEY:
			_key = 8;
			break;
		}

		do {
			x = rand() % (b->getBoardWidth() - 1);
			y = rand() % 4 + _key;
		} while (!bt->isElgibleToPos(x, y, _b) 
				|| isAnyToolInPos(x, y));

		bt->set(x, y);
	}

	bool isAnyToolInPos(int x, int y) {
		return getToolInPos(x,y) != NULL;
	}
	bool isFriends(BoardTool* bta, BoardTool* btb) {
		return isInToolInA(bta) == isInToolInA(btb);
	}

	bool isInToolInA(BoardTool* bt) {
		switch (bt->getC())
		{
		case 'A':
		case 'B':
		case 'C':
			return true;
		default:
			return false;
		}

	}

	BoardTool* getToolInPos(int x, int y) {

		for (int i = 0; i < TOOLS_COUNT; ++i) {
			if (ATools[i].isOnPos(x,y))
				return &ATools[i];
			if (BTools[i].isOnPos(x,y))
				return &BTools[i];
		}
		return NULL;
	}

	void printToolsOnBoard(BoardTool * playerTools) {
		for (int i = 0; i < TOOLS_COUNT; ++i) {
			BoardTool* tool = &playerTools[i];
			if (tool->isLive())
				_b->printCellByPos(tool->getC(), tool->getX(), tool->getY(), tool->getColor());
		}
	}

	void keyPressed(char c) {
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
			_changeDir(c);
			break;
		}
	}

	void _changeDir(char c) {
		if (selectedA != -1 && getDirA((Direction_A)c) != Direction::NONE) {
			if (ATools[selectedA].setDirection(getDirA((Direction_A)c)))
				selectedA = -1;
		}
		if (selectedB != -1 && getDirB((Direction_E)c) != Direction::NONE) {
			if (BTools[selectedB].setDirection(getDirB((Direction_E)c)))
				selectedB = -1;

		}
	}

	Direction getDirB(Direction_E dir) {
		switch (dir) {
		case Direction_E::UP:
			return Direction::UP;
		case Direction_E::DOWN:
			return Direction::DOWN;
		case Direction_E::LEFT:
			return Direction::LEFT;
		case Direction_E::RIGHT:
			return Direction::RIGHT;
		default: 
			return Direction::NONE;
		}
	}

	Direction getDirA(Direction_A dir) {
		switch (dir) {
		case Direction_A::UP:
			return Direction::UP;
		case Direction_A::DOWN:
			return Direction::DOWN;
		case Direction_A::LEFT:
			return Direction::LEFT;
		case Direction_A::RIGHT:
			return Direction::RIGHT;
		default: 
			return Direction::NONE;
		}
	}

	void _initGame(Player* pa, Player* pb) {
		_setTools(ATools, aColor, A_KEY);
		_setTools(BTools, bColor, B_KEY);
		_b->printBoard(pa,aColor, pb, bColor);
		printToolsOnBoard();
	}

	void printToolsOnBoard() {
		printToolsOnBoard(ATools);
		printToolsOnBoard(BTools);
	}
};