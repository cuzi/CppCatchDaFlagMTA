#pragma once

#include <Windows.h>
#include <conio.h>
#include "stdafx.h"
#include "Board.h"
#include "Player.h"
#include "BoardTool.h"
#include "Position.h"
#include <vector>
#include <iterator>
#include <algorithm>
#include <errno.h>
#include "Move.h"

class Player;
class Board;
class BoardTool;

class GameManager {
	enum { RESUME = 1, RESTART = 2,RECORD_GAME=5, MAIN_MENU = 8, EXIT = 9 };
	enum { A = 1, B = 2, C = 3, E = 7, F = 8, G = 9 };
	string txt[9] = { "Resume", "Restart Game", "", "","Start Record Game","","","Main Menu", "Exit Game" };

	//if loaded game
	bool LOADED = false;
	bool RECORD = false;
	std::vector< string > err_stack;

	string boardFilePath;
	string moveAFilePath;
	string moveBFilePath;

	// SAVE
	//TODO: write function that check if file exist on fs , if so, add suffic _new until current file wont exist
	//TODO: do this check outside and when init GM ctor, give good paths, there is no need to set this vals
	//TODO: each GM ctor init gameIndex will increased
	string gameSavingPath = "";
	string gamePrefixPath = (gameSavingPath == "") ? "CatchTheFlage_" + to_string(gameIndex) : "/CatchTheFlage_" + to_string(gameIndex);
	
	vector<Move> aMoves;
	vector<Move> bMoves;

	static const int TOOLS_COUNT = 3;

	BoardTool* ATools;
	BoardTool* BTools;

	int aColor = BLUE;
	int bColor = RED;

	int clock = 0;

	static const int A_KEY = A;
	static const int B_KEY = E;

	int selectedA = -1, selectedB = -1;
	

	enum { ESC = 27 };

	Board* _b;

public:
	static int gameIndex;

	GameManager(Board * b) : _b(b) { gameIndex++; }
	~GameManager();

	void editSubMenu(int key, string msg) {
		txt[key] = msg;
	}
	void addErrorMsg(string msg) {
		err_stack.push_back(msg);
	}
	void start(Player* pa, Player *pb);
	bool isFriends(BoardTool* bta, BoardTool* btb);
	void fight(BoardTool* bta, BoardTool* btb);
	BoardTool* getToolInPos(int x, int y);
	void setBoard(string filePath) {
		boardFilePath = filePath;
		LOADED = true;
	}
	void setMoves(string playerAmoves="", string playerBmoves="") {
		moveAFilePath = playerAmoves;
		moveBFilePath = playerBmoves;
		LOADED = true;

	}
	bool isAnyToolInPos(int x, int y) {
		return getToolInPos(x, y) != NULL;
	}
	void startRecord() {
		RECORD = true;
	}
	void endRecord() {
		RECORD = false;
	}
	bool isRecording() {
		return RECORD;
	}

private:
	void loadBoardLine(std::string line, int lineIdx, Position* pa, Position* pb);
	int loadFromFile(string filePath, Position* pa, Position* pb);
	int saveBoardToFile(string filePath, Player* pa, Player* pb);
	int GameManager::saveMoveToFile(string filePath, Move m);
	bool isGameFreezed();
	Move getNextMove(int playerKey);
	int autoGameLoop(Player* pa, Player* pb);
	int gameLoop(Player* pa, Player* pb);
	bool gameStatus(Player* pa, Player* pb);
	void toolHit(BoardTool* bt, BoardTool* btb);
	// If submenu return true the game need to be stopped
	bool showSubMenu(Player* pa, Player* pb);
	void _setRandomTools(BoardTool* playerTools, int color, int key);
	void _gameWin(Player *p);
	bool _initGame(Player* pa, Player* pb);
	void _markPlayersOnBoard(Player* pa, Player* pb);
	void _unMarkPlayersOnBoard(Player* pa, Player* pb);
	void printToolsOnBoard(BoardTool * playerTools);
	BoardTool *_getTools(int key);
	void _setRandomToolPos(Board *b, BoardTool *bt, int key);
	bool isToolInA(BoardTool* bt);
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
	void _setTools(BoardTool* playerTools, int color, Position* aPos);
	void _setToolPos(Board *b, BoardTool *bt, Position p);
	void printStackTrace();
	bool CheckBoard();
	void pushErrMsg(string msg) {
		if (std::find(err_stack.begin(), err_stack.end(), msg) == err_stack.end()) {
			// msg not in err_stack, add it
			err_stack.push_back(msg);
		}
	}
	void clearCls() {
		system("cls");
	}
	int loadMoves(string filePath, int playerKey);
	Move _parseMove(string move);
};