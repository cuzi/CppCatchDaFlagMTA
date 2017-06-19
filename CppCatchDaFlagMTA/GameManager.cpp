#include "stdafx.h"
#include "GameManager.h"
#include <exception>
#include "Game.h"
#include "AlgorithmRegisteration.h"
#include <functional>
#include <map>

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

void GameManager::loadBoardLine(std::string line, int lineNumber, Position* pa, Position* pb) {
	
	for (unsigned i = 0; i < line.length(); ++i)
	{
		switch (line.at(i)) {
		case 'T':
			_b->setBoardCell(lineNumber, i, Board::FR);
			break;
		case 'S':
			_b->setBoardCell(lineNumber, i,Board::SEA);
			break;
		case 'A':
			_b->setBoardCell(lineNumber, i, Board::FlgA);
			break;
		case 'B':
			_b->setBoardCell(lineNumber, i, Board::FlgB);
			break;
		case '1':
			pa[0].set(lineNumber, i, A);
			break;
		case '2':
			pa[1].set(lineNumber, i, B);
			break;
		case '3':
			pa[2].set(lineNumber, i, C);
			break;
		case '7':
			pb[0].set(lineNumber, i, E);
			break;
		case '8':
			pb[1].set(lineNumber, i, F);
			break;
		case '9':
			pb[2].set(lineNumber, i, G);
			break;
		default:
			// leave cell EMPTY
			break;
		}
	}
}

int GameManager::loadFromFile(string filePath, Position* pa, Position* pb)
{
	std::ifstream bfile;
	bfile.open(filePath, ios::in);
	if (bfile.is_open()) {
		std::string str;
		int lineIdx = 0;
		while (std::getline(bfile, str) && lineIdx < _b->getBoardHeigth())
		{
			std::string board_line = str.substr(0, _b->getBoardWidth());
			loadBoardLine(board_line, lineIdx, pa, pb);
			++lineIdx;
		}
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

int GameManager::start(Player* pa, Player* pb) {
	int winner;	
	++_cycle;
	setFilePath();

	bool is_not_init = _initGame(pa, pb);

	if (!is_not_init) {
		if (LOADED) {
			winner = autoGameLoop(pa, pb);

			_gameWinAuto(winner == -1 ? NULL : 
				(winner == Player::A ? pa : pb), 5);
		}
		//TODO: CREATE NEW MENU FOR ALGO RUNNIG , FOR NOW ITS ONLY BOOL THAT DIRECT FOR THIS ELSE CLAUSE
		else if (ALGO) {

			AlgorithmPlayer * alga = new AlgorithmPlayer();
			AlgorithmPlayer * algb = new AlgorithmPlayer();
			BoardData * P1abd = new AlgoBoardData(_b->getBoard(),ATools, BTools, 1);
			BoardData * P2abd = new AlgoBoardData(_b->getBoard(), ATools, BTools, 2);

			alga->setPlayer(1);
			algb->setPlayer(2);

			alga->init(*P1abd);
			algb->init(*P2abd);

			winner = NewGameLoop(pa,pb,alga,algb );

			_gameWinAuto(winner == -1 ? NULL :
				(winner == Player::A ? pa : pb), 5);

		}
		else {
			winner = gameLoop(pa, pb);
			if (winner != STOP && winner != CLOSE) _gameWin(winner == Player::A ? pa : pb);
			else if (winner == CLOSE) return EXIT;
		}

		
		LOADED = false;
		_b->initBoard();
		setTextColor(WHITE);
	}	
	return !is_not_init;
}

int GameManager::gameLoop(Player* pa, Player* pb) {
	bool gameOn = true;
	char ch = 0;
	clock = 0;

	// set first player
	int playing = (clock % 2 ? A_KEY : B_KEY);

	while (gameOn && _isOpAlive(playing)) {
		playing = (clock % 2 ? A_KEY : B_KEY);  // don't move it to the end of the loop!

		Sleep(delay - 10);

		if (_kbhit()) {
			ch = _getch();
			keyPressed(ch);
		}

		gameOn = !_moveTools(playing);
		clock++;

		if (ch == ESC) {
			int subMenuAns = showSubMenu(pa, pb);
			if (subMenuAns == STOP)
				return STOP;
			if (subMenuAns == CLOSE)
				return CLOSE;
			ch = 0;
		}
		std::cin.clear();
	}
	return playing;
}

bool GameManager::_isOpAlive(char player) {
	BoardTool* opTools = player == Player::A ? BTools : ATools;
	return _isLiveTools(opTools);
}
bool GameManager::_isLiveTools(BoardTool* tools) {
	for (int i = 0; i < TOOLS_COUNT; ++i) {
		if ((tools + i)->isLive())
			return true;
	}
	return false;
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

int GameManager::NewGameLoop(Player* a, Player* b, AlgorithmPlayer* pa, AlgorithmPlayer* pb) {
	bool gameOn = true;
	char ch = 0;
	clock = 0;
	int round = 0;
	AlgorithmPlayer * curr_player;
	GameMove * last_move = &GameMove(0,0,0,0);

	// set first player
	int playing = (clock % 2 ? A_KEY : B_KEY);

	while (gameOn && _isOpAlive(playing)) {
		playing = (clock % 2 ? A_KEY : B_KEY);  // don't move it to the end of the loop!

		Sleep(delay - 10);

		curr_player = (playing == A_KEY ? pa : pb);
		last_move = &curr_player->play(*last_move);
		if (!_runMove(*last_move, playing)) {
			last_move = &GameMove(last_move->from_x, last_move->from_y,
				last_move->from_x, last_move->from_y);
		}

		if (last_move->to_y == 0 && last_move->to_x == 9) {
			int a = 1;
		}

		gameOn = !_moveTools(playing,TRUE);
		clock++;

		if (ch == ESC) {
			int subMenuAns = showSubMenu(a, b);
			if (subMenuAns == STOP)
				return STOP;
			if (subMenuAns == CLOSE)
				return CLOSE;
			ch = 0;
		}
		std::cin.clear();
		round++;
		if (gameOn){
			gameOn = (round < ALGOLOOP) ? true : false;
		}
	}
	return playing;
}


int GameManager::autoGameLoop(Player* pa, Player* pb) {
	bool gameOn = true;

	clock = 0;
	Move aNextMove = getNextMove(A_KEY);
	Move bNextMove = getNextMove(B_KEY);

	// set first player
	int playing = (clock % 2 ? A_KEY : B_KEY);

	while (gameOn ) {
		playing = (clock % 2 ? A_KEY : B_KEY);  // don't move it to the end of the loop!
		

		Sleep(QUIET ? 0 : delay);
		if (aNextMove.getClockTime() == -1 && bNextMove.getClockTime() == -1 && isGameFreezed()) {
			gameOn = false;
			playing = -1;
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

			std::cin.clear();
		}
		
	}
	return playing;
}


int GameManager::showSubMenu(Player* pa, Player* pb) {
	int i;
	clearCls();
	_printSubMenu();

	cin >> i;

	switch (i) {
	case RESUME:
		_b->printBoard(pa, aColor, pb, bColor);
		printToolsOnBoard();
		return RESUME;
		break;
	case RESTART:
		start(pa, pb);
		return STOP;
		break;
	case RECORD_GAME:
		(!isRecording()) ? startRecord() : endRecord();
		editSubMenu(4, (isRecording()) ? "Stop record game" : "Start record game");
		_b->printBoard(pa, aColor, pb, bColor);
		printToolsOnBoard();
		return RESUME;
		break;
	case MAIN_MENU:
		LOADED = false;
		_b->initBoard();
		return STOP;
		break;
	case EXIT:
		_b->cleanBoard();
		cout << "bye bye";
		Sleep(delay * BIG_DELAY);
		return CLOSE;
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
	Sleep(delay * BIG_DELAY);
}
void GameManager::_gameWinAuto(Player *p, int totalMoves) {
	_b->cleanBoard();
	if (p != NULL) p->win();
	cout << "Game cycle : "<< _cycle << endl ;
	cout << "Num moves : " << totalMoves << endl;
	cout << "Winner : " << (p == NULL ? "NONE" : p->getName()) << endl;

	Sleep(delay * BIG_DELAY);
}

bool GameManager::_initGame(Player* pa, Player* pb) {
	bool err = false;
	int errCode;

	ATools = new BoardTool[TOOLS_COUNT];
	BTools = new BoardTool[TOOLS_COUNT];

	if (LOADED) {
		Position APositions[TOOLS_COUNT];
		Position BPositions[TOOLS_COUNT];
		errCode = loadFromFile(boardFilePath, APositions, BPositions);
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
		_b->configRandBoardCells();

		_setRandomTools(ATools, aColor, A_KEY);
		_setRandomTools(BTools, bColor, B_KEY);
	}

	if (!err) {
		if (isRecording())
			saveBoardToFile(gamePrefixPath + "." + BOARD_EXT, pa, pb);
		if (!QUIET) {
			_b->printBoard(pa, aColor, pb, bColor);
			printToolsOnBoard();
		}
	}
	else {
		_b->cleanBoard();
		printStackTrace();
		unSetBoard();
		unSetMoves();
		Sleep(delay * BIG_DELAY);
		clearCls();
	}
	return err;
}

void GameManager::_markPlayersOnBoard(Player * pa, Player * pb)
{
	for (int i = 0;i < TOOLS_COUNT;i++) {
		_b->setBoardCell(ATools[i].getX(), ATools[i].getY(), Board::getBoardKey(ATools[i].getC()));
		_b->setBoardCell(BTools[i].getX(), BTools[i].getY(), Board::getBoardKey(BTools[i].getC()));
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
		x = rand() % 4 + _key;
		y = rand() % (b->getBoardWidth() - 1);
	} while (! b->isCellEmpty(x, y)
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

bool GameManager::_moveTools(int key,bool one_step) {
	bool win = false;
	for (int i = 0; i < TOOLS_COUNT; ++i) {
		win = win || (_getTools(key))[i].move(_b, this, !QUIET, one_step);
	}

	return win;
}

void GameManager::_stopTools(BoardTool* tools) {
	for (int i = 0; i < TOOLS_COUNT; ++i) {
		(tools + i)->stop();
	}
}

char GameManager::convertGameMoveToDir(const GameMove& m, int player_key) {
	int _dir_x = m.to_x - m.from_x;
	int _dir_y = m.to_y - m.from_y;

	if (player_key == A_KEY) {
		if (_dir_x != 0) {
			return (_dir_x > 0) ? (char)Direction_A::RIGHT : (char)Direction_A::LEFT;
		}
		else {
			return (int)(_dir_y > 0) ? (char)Direction_A::DOWN : (char)Direction_A::UP;
		}
	}
	else {
		if (_dir_x != 0) {
			return (_dir_x > 0) ? (char)Direction_E::RIGHT : (char)Direction_E::LEFT;
		}
		else {
			return (_dir_y > 0) ? (char)Direction_E::DOWN : (char)Direction_E::UP;
		}
	}
	
}

int  GameManager::searchInTools(int x, int y) const {

	for (int i = 0;i < TOOLS_COUNT;i++) {
		if (x == ATools[i].getX() && y == ATools[i].getY())
			return ATools[i].getC() - '0';
		if (x == BTools[i].getX() && y == BTools[i].getY())
			return BTools[i].getC() - '0';
	}
	return -1;
}

bool GameManager::_runMove(const GameMove& m,int player_key) {
	char dir;
	int toolKey = searchInTools(m.from_y, m.from_x);
	keyPressed('0' + toolKey);
	dir = convertGameMoveToDir(m, player_key);
	_changeDir(dir);

	if (toolKey == searchInTools(m.to_y, m.to_x)) {
		return true;
	}
	else {
		return false;
	}
}

void GameManager::_changeDir(char c) {

	if (selectedA != -1 && getDirA((Direction_A)c) != Direction::NONE) {
		_stopTools(ATools);
		if (ATools[selectedA].setDirection(getDirA((Direction_A)c))) {
			if (RECORD)
				saveMoveToFile(gamePrefixPath + "." + MOVES_A_EXT, Move(clock, selectedA + 1, Move::getPlayerAdir(c)));
		}
	}
	if (selectedB != -1 && getDirB((Direction_E)c) != Direction::NONE) {
		_stopTools(BTools);
		if (BTools[selectedB].setDirection(getDirB((Direction_E)c))) {
			if (RECORD)
				saveMoveToFile(gamePrefixPath + "." + MOVES_B_EXT, Move(clock, selectedB + 1, Move::getPlayerEdir(c)));
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