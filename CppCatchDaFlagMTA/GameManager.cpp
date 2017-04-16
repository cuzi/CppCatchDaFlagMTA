#include "stdafx.h"
#include "GameManager.h"

GameManager::~GameManager() {
	free(ATools);
	free(BTools);
}

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


bool GameManager::showSubMenu(Player* pa, Player* pb) {
	int i;

	_printSubMenu();

	cin >> i;

	switch (i) {
	case RESUME:
		_b->printBoard(pa, aColor, pb, bColor);
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

void GameManager::_setTools(BoardTool* playerTools, int color, int key) {

	for (int i = 0; i < TOOLS_COUNT; ++i) {
		(playerTools + i)->setColor(color);
		(playerTools + i)->setChar('0' + i + key);
		_setToolPos(_b, (playerTools + i), key);
		(playerTools + i)->init();
	}
}

void GameManager::_gameWin(Player *p) {
	_b->cleanBoard();
	p->win();
	_printGameOver();
	cout << p->getName() << " Won the game!\n";
	_playWinSound();
	Sleep(1250);
}

void GameManager::_initGame(Player* pa, Player* pb) {
	ATools = new BoardTool[TOOLS_COUNT];
	BTools = new BoardTool[TOOLS_COUNT];

	_setTools(ATools, aColor, A_KEY);
	_setTools(BTools, bColor, B_KEY);
	_b->printBoard(pa, aColor, pb, bColor);
	printToolsOnBoard();
}


void GameManager::printToolsOnBoard(BoardTool * playerTools) {
	for (int i = 0; i < TOOLS_COUNT; ++i) {
		BoardTool* tool = &playerTools[i];
		if (tool->isLive())
			_b->printCellByPos(tool->getC(), tool->getX(), tool->getY(), tool->getColor());
	}
}

BoardTool* GameManager::_getTools(int key) {
	return (key == A_KEY ? ATools : BTools);
}

void GameManager::_setToolPos(Board *b, BoardTool *bt, int key) {
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
	} while (!bt->isElgibleToPos(x, y, _b, this)
		|| isAnyToolInPos(x, y));

	bt->set(x, y);
}

bool GameManager::isInToolInA(BoardTool* bt) {
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

BoardTool* GameManager::getToolInPos(int x, int y) {

	for (int i = 0; i < TOOLS_COUNT; ++i) {
		if (ATools[i].isOnPos(x, y))
			return &ATools[i];
		if (BTools[i].isOnPos(x, y))
			return &BTools[i];
	}
	return NULL;
}

bool GameManager::isFriends(BoardTool* bta, BoardTool* btb) {
	return isInToolInA(bta) == isInToolInA(btb);
}

bool GameManager::_moveTools(int key) {
	bool win = false;
	for (int i = 0; i < TOOLS_COUNT; ++i) {
		win = win || (_getTools(key))[i].move(_b, this);
	}

	return win;
}

void GameManager::_changeDir(char c) {
	if (selectedA != -1 && getDirA((Direction_A)c) != Direction::NONE) {
		if (ATools[selectedA].setDirection(getDirA((Direction_A)c)))
			selectedA = -1;
	}
	if (selectedB != -1 && getDirB((Direction_E)c) != Direction::NONE) {
		if (BTools[selectedB].setDirection(getDirB((Direction_E)c)))
			selectedB = -1;
	}
}

void GameManager::keyPressed(char c) {
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

void GameManager::_printSubMenu() {
	_b->cleanBoard();
	cout << "Game Stopped\n";
	cout << "Choose from the following:\n";
	for (int i = 0; i < EXIT; ++i) {
		_printLine(i);
	}
}