#include "stdafx.h"
#include "GameManager.h"

GameManager::~GameManager() {
	free(ATools);
	free(BTools);
}

int GameManager::saveBoardToFile(string filePath, Player* pa, Player* pb) {
	std::ofstream bfile;
	bfile.open(filePath, ios::out);
	if (bfile.is_open()) {
		_markPlayersOnBoard(pa, pb);
		bfile << *_b;
		_unMarkPlayersOnBoard(pa, pb);
	}
	else
		return errno;
	return 0;
}

int GameManager::saveMoveToFile(string filePath,Move m) {
	std::ofstream bfile;
	bfile.open(filePath, ios::app);
	if (bfile.is_open()) {
		bfile << m;
	}
	else
		return errno;
	return 0;
}

void GameManager::start(Player* pa, Player* pb) {
	int winner;	
	bool is_not_init = _initGame(pa, pb);
	if (!is_not_init) {
		if (LOADED)
			winner = autoGameLoop(pa, pb);
		else
			winner = gameLoop(pa, pb);

		if (winner != -1)
			_gameWin(winner == Player::A ? pa : pb);
		
		LOADED = false;
		_b->initBoard();
		setTextColor(WHITE);
	}	
}

int GameManager::gameLoop(Player* pa, Player* pb) {
	bool gameOn = true;
	char ch = 0;
	clock = 0;

	// set first player
	int playing = (clock % 2 ? A_KEY : B_KEY);

	while (gameOn && gameStatus(pa, pb)) {
		playing = (clock % 2 ? A_KEY : B_KEY);  // don't move it to the end of the loop!

		Sleep(200);

		if (_kbhit()) {
			ch = _getch();
			keyPressed(ch);
		}

		gameOn = !_moveTools(playing);
		clock++;

		if (ch == ESC) {
			if (showSubMenu(pa, pb))
				return -1;
			ch = 0;
		}
		std::cin.clear();
	}
	return playing;
}

Move GameManager::getNextMove(int playerKey) {
	vector<Move>& moves = (playerKey == A_KEY) ? aMoves : bMoves;

	if (!moves.empty()) {
		Move move = moves.front();
		moves.erase(moves.begin());
		return move;
	}
	else
		// no moves left
		// return dummy move
		return Move(-1, -1,'0');
}

bool GameManager::isGameFreezed() {
	for (int i = 0;i < TOOLS_COUNT;i++) {
		if (ATools[i].isMoving() || BTools[i].isMoving())
			return false;
	}
	return true;
}

int GameManager::autoGameLoop(Player* pa, Player* pb) {
	bool gameOn = true;
	char ch = 0;

	clock = 0;
	Move aNextMove = getNextMove(A_KEY);
	Move bNextMove = getNextMove(B_KEY);

	// set first player
	int playing = (clock % 2 ? A_KEY : B_KEY);

	while (gameOn && gameStatus(pa, pb)) {
		playing = (clock % 2 ? A_KEY : B_KEY);  // don't move it to the end of the loop!
		

		Sleep(200);
		if (aNextMove.getClockTime() == -1 && bNextMove.getClockTime() == -1 && isGameFreezed()) {
			gameOn = false;
		}
		else {
			if (clock == aNextMove.getClockTime()) {
				keyPressed(aNextMove.getTool());
				keyPressed(Move::getPlayerAdir(aNextMove.getDir()));
				aNextMove = getNextMove(A_KEY);
			}
			if (clock == bNextMove.getClockTime()) {
				keyPressed(bNextMove.getTool());
				keyPressed(Move::getPlayerEdir(bNextMove.getDir()));
				bNextMove = getNextMove(B_KEY);
			}

			gameOn = !_moveTools(playing);
			clock++;

			if (ch == ESC) {
				if (showSubMenu(pa, pb))
					return -1;
				ch = 0;
			}
			std::cin.clear();
		}
		
	}
	return playing;
}

bool GameManager::gameStatus(Player* pa, Player* pb) {
	// TODO check logic in tools positions if there is tools in same position 
	//		need to check who win and return false if some player have no tools
	return true;
}

bool GameManager::showSubMenu(Player* pa, Player* pb) {
	int i;
	clearCls();
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
		LOADED = false;
		_b->initBoard();
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

void GameManager::_setTools(BoardTool* playerTools, int color, Position* p) {
	for (int i = 0; i < TOOLS_COUNT; ++i) {
		if (p[i].isPositionSet()) {
			(playerTools + i)->setColor(color);
			(playerTools + i)->setChar('0' + p[i].getC());
			_setToolPos(_b, (playerTools + i), p[i]);
			(playerTools + i)->init();
		}
	}
}

void GameManager::_setRandomTools(BoardTool* playerTools, int color, int key) {

	for (int i = 0; i < TOOLS_COUNT; ++i) {
		(playerTools + i)->setColor(color);
		(playerTools + i)->setChar('0' + i + key);
		_setRandomToolPos(_b, (playerTools + i), key);
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

bool GameManager::_initGame(Player* pa, Player* pb) {
	bool err = false;
	int errCode;

	ATools = new BoardTool[TOOLS_COUNT];
	BTools = new BoardTool[TOOLS_COUNT];

	if (LOADED) {
		Position APositions[TOOLS_COUNT];
		Position BPositions[TOOLS_COUNT];
		errCode = _b->loadFromFile(boardFilePath, APositions, BPositions);
		loadMoves(moveAFilePath, A_KEY);
		loadMoves(moveBFilePath, B_KEY);
		
		if (!errCode) {
			_setTools(ATools, aColor, APositions);
			_setTools(BTools, bColor, BPositions);
			err = CheckBoard();
		}
		else {
			char buffer[255];
			strerror_s(buffer, errCode);
			pushErrMsg(boardFilePath + "\n" + buffer);
			err = true;
		}
			
	}
	else {
		_setRandomTools(ATools, aColor, A_KEY);
		_setRandomTools(BTools, bColor, B_KEY);
		_b->configRandBoardCells();
	}

	if (!err) {
		if (isRecording())
			saveBoardToFile(gamePrefixPath + ".gboard", pa, pb);
		
		_b->printBoard(pa, aColor, pb, bColor);
		printToolsOnBoard();
	}
	else {
		_b->cleanBoard();
		printStackTrace();
		Sleep(3500);
		clearCls();
	}
	return err;
}

void GameManager::_markPlayersOnBoard(Player * pa, Player * pb)
{
	for (int i = 0;i < TOOLS_COUNT;i++) {
		_b->setBoardCell(ATools[i].getX(), ATools[i].getY(), ATools[i].getC());
		_b->setBoardCell(BTools[i].getX(), BTools[i].getY(), BTools[i].getC());
	}
}

void GameManager::_unMarkPlayersOnBoard(Player * pa, Player * pb)
{
	for (int i = 0;i < TOOLS_COUNT;i++) {
		_b->setBoardCell(ATools[i].getX(), ATools[i].getY(), Board::EMPTY);
		_b->setBoardCell(BTools[i].getX(), BTools[i].getY(), Board::EMPTY);
	}
}

void GameManager::printStackTrace() {
	// eliminate duplicate values
	std::ostream_iterator< string > output(cout, "\n");
	//endLocation = std::unique(err_stack.begin(), err_stack.end());
	cout << "An error occoured while trying to load game board:";
	cout << endl;
	std::copy(err_stack.begin(), err_stack.end(), output);
	err_stack.clear();
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

void GameManager::_setRandomToolPos(Board *b, BoardTool *bt, int key) {
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

void GameManager::_setToolPos(Board *b, BoardTool *bt, Position p) {
	int x = p.getX();
	int y = p.getY();
	if (bt->isElgibleToPos(x, y, _b, this) && !(isAnyToolInPos(x,y))) {
		bt->set(x, y);
	 }
}

bool GameManager::CheckBoard()
{
	bool err = false;
	int aFlgCnt = 0, bFlgCnt = 0;
	for (int i = 0;i < TOOLS_COUNT;i++) {
		if (!ATools[i].isLive()) {
			err = true;
			pushErrMsg("Wrong settings for player A tools in file " + boardFilePath);
		}
		if (!BTools[i].isLive()) {
			err = true;
			pushErrMsg("Wrong settings for player B tools in file " + boardFilePath);
		}
	}
	for (int i = 0;i < _b->getBoardHeigth();i++) {
		for (int j = 0; j < _b->getBoardWidth(); j++) {
			if (_b->GetCell(i, j) == Board::FlgA)
				aFlgCnt++;
			if (_b->GetCell(i, j) == Board::FlgB)
				bFlgCnt++;
		}
	}

	if (bFlgCnt != 1) {
		pushErrMsg(to_string(bFlgCnt) + " Flags of type B is configured in file " + boardFilePath);
		err = true;
	}
	if (aFlgCnt != 1) {
		pushErrMsg(to_string(aFlgCnt) + " Flags of type A is configured in file " + boardFilePath);
		err = true;
	}
	return err;
}

int GameManager::loadMoves(string filePath, int playerKey)
{
	vector<Move>& moves = (playerKey == A_KEY)? aMoves : bMoves;
	std::ifstream bfile;
	bfile.open(filePath, ios::in);
	if (bfile.is_open()) {
		std::string str;
		while (std::getline(bfile, str))
		{
			moves.push_back(_parseMove(str));
		}
	}
	else
		return errno;

	return 0;
}

Move GameManager::_parseMove(string move)
{
	string arr[3];
	int i = 0;
	std::string delimiter = ",";
	size_t pos = 0;
	std::string token;

	while ((pos = move.find(delimiter)) != std::string::npos) {
		token = move.substr(0, pos);
		arr[i] = token;
		move.erase(0, pos + delimiter.length());
		++i;
	}

	token = move.substr(0, pos);
	arr[i] = token;

	return Move(std::stoi(arr[0]), arr[1][0], arr[2][0]);
}

bool GameManager::isToolInA(BoardTool* bt) {
	switch (bt->getC())
	{
	case '1':
	case '2':
	case '3':
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
	return isToolInA(bta) == isToolInA(btb);
}

void GameManager::fight(BoardTool* bta, BoardTool* btb) {
	if (isFriends(bta, btb))
		return;
	if (isToolInA(bta))
		toolHit(bta, btb);
	else
		toolHit(btb, bta);
}

void GameManager::toolHit(BoardTool* Atool, BoardTool* Btool) {

	int x = Atool->getX(), y = Atool->getY();

	switch (Atool->getC())
	{
	case A + '0':
		if (x == 3 || (y >= 9 && y < 13))
			Atool->die();
		else Btool->die();
		break;
	case B + '0':
		if (Btool->getC() != G + '0' && (x == 6 || y == 2 || y == 3))
			Btool->die();
		else Atool->die();

		break;
	case C + '0':
		if (x == 3 || y == 7)
			Btool->die();
		else Atool->die();
		break;
	default:
		break;
	}
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
		if (ATools[selectedA].setDirection(getDirA((Direction_A)c))) {
			Move(clock, selectedA, c);
			if (RECORD)
				saveMoveToFile(gamePrefixPath + ".moves-a_small", Move(clock, selectedA + 1, Move::getPlayerAdir(c)));
			selectedA = -1;			
		}
	}
	if (selectedB != -1 && getDirB((Direction_E)c) != Direction::NONE) {
		if (BTools[selectedB].setDirection(getDirB((Direction_E)c))) {
			if (RECORD)
				saveMoveToFile(gamePrefixPath + ".moves-b_small", Move(clock, selectedB + 1, Move::getPlayerEdir(c)));
			selectedB = -1;
		}
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