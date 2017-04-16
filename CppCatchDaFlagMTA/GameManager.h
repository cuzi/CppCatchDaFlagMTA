#pragma once

#include <Windows.h>
#include <conio.h>
#include "stdafx.h"
#include "Board.h"
#include "Player.h"
#include "BoardTool.h"

class Player;
class Board;
class BoardTool;

class GameManager {
	enum { RESUME = 1, RESTART = 2, MAIN_MENU = 8, EXIT = 9 };
	enum { A = 1, B = 2, C = 3, E = 7, F = 8, G = 9 };

	char* txt[9] = { "Resume", "Restart Game", "", "","","","","Main Menu", "Exit Game" };

	static const int TOOLS_COUNT = 3;

	BoardTool* ATools;
	BoardTool* BTools;

	int aColor = BLUE;
	int bColor = RED;

	static const int A_KEY = A;
	static const int B_KEY = E;

	int selectedA = -1, selectedB = -1;


	enum { ESC = 27 };

	Board* _b;

public:
	GameManager(Board * b) : _b(b) {}
	~GameManager();

	void start(Player* pa, Player *pb);
	bool isFriends(BoardTool* bta, BoardTool* btb);
	void fight(BoardTool* bta, BoardTool* btb);
	BoardTool* getToolInPos(int x, int y);

	bool isAnyToolInPos(int x, int y) {
		return getToolInPos(x, y) != NULL;
	}
private:
	bool gameStatus(Player* pa, Player* pb);

	// If submenu return true the game need to be stopped
	bool showSubMenu(Player* pa, Player* pb);
	void _setTools(BoardTool* playerTools, int color, int key);
	void _gameWin(Player *p);
	void _initGame(Player* pa, Player* pb);
	void printToolsOnBoard(BoardTool * playerTools);
	BoardTool *_getTools(int key);
	void _setToolPos(Board *b, BoardTool *bt, int key);
	bool isInToolInA(BoardTool* bt);
	bool _moveTools(int key);
	void _changeDir(char c);
	void keyPressed(char c);
	void _printSubMenu();

	void _printLine(int i) {
		if (txt[i] != "") {
			cout << "  " << (i + 1) << " - " << txt[i] << endl;
		}
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

	void printToolsOnBoard() {
		printToolsOnBoard(ATools);
		printToolsOnBoard(BTools);
	}
};