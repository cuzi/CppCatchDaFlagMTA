#include "stdafx.h"
#include "Board.h"


string Board::getScoreString(Player* p) {
	return p->getName() + ": " + to_string(p->getScore());
}

void Board::loadBoardLine(std::string line, int lineNumber, Position* APositions, Position* BPositions) {
	for (unsigned i = 0; i < line.length(); ++i)
	{
		switch (line.at(i)) {
		case 'T':
			boardCells[lineNumber][i] = FR;
			break;
		case 'S':
			boardCells[lineNumber][i] = SEA;
			break;
		case 'A':
			boardCells[lineNumber][i] = FlgA;
			break;
		case 'B':
			boardCells[lineNumber][i] = FlgB;
			break;
		case '1':
			APositions[0].set(lineNumber, i, A);
			break;
		case '2':
			APositions[1].set(lineNumber, i, B);
			break;
		case '3':
			APositions[2].set(lineNumber, i, C);
			break;
		case '7':
			BPositions[0].set(lineNumber, i, E);
			break;
		case '8':
			BPositions[1].set(lineNumber, i, F);
			break;
		case '9':
			BPositions[2].set(lineNumber, i, G);
			break;
		default:
			// leave cell EMPTY
			break;
		}
	}
}
void Board::printScoreBoard(Player* a, int aColor, Player* b, int bColor) {
	int halfWidth = (BOARD_TAB * (_colSize + 1) + 1) / 2;

	gotoxy(0, 0);
	setTextColor(aColor);
	cout << left << setw(halfWidth) << getScoreString(a);
	setTextColor(bColor);
	cout << right << setw(halfWidth) << getScoreString(b) << endl;
	setTextColor(WHITE);
}
void Board::printheadline()
{
	gotoxy(0, 1);

	printCell(" "); // print empty cell
	for (int i = 0; i < _colSize; i++) {
		printCell(string(1, 'a' + i));
	}
	cout << endl;
	printBoardline();
}
void Board::configRandBoardCells()
{
	boardCells[6][0] = FR;
	boardCells[7][0] = FR;
	boardCells[3][2] = FR;
	boardCells[6][1] = FR;
	boardCells[12][1] = FlgB;
	boardCells[4][2] = FR;
	boardCells[5][2] = FR;
	boardCells[6][2] = FR;
	boardCells[5][3] = FR;
	boardCells[6][3] = FR;
	boardCells[7][3] = FR;
	boardCells[8][3] = FR;
	boardCells[5][7] = SEA;
	boardCells[4][8] = SEA;
	boardCells[5][8] = SEA;
	boardCells[3][9] = SEA;
	boardCells[4][9] = SEA;
	boardCells[5][9] = SEA;
	boardCells[6][9] = SEA;
	boardCells[7][9] = SEA;
	boardCells[8][9] = SEA;
	boardCells[0][10] = FlgA;
	boardCells[6][10] = SEA;
	boardCells[7][10] = SEA;
	boardCells[8][10] = SEA;
	boardCells[7][11] = SEA;

}
void Board::freeBoardMat()
{
	// free dynamically allocated memory
	for (int i = 0; i < _rowSize; i++)
	{
		delete[] boardCells[i]; // delete array within matrix
	}
	// delete actual matrix
	delete[] boardCells;
}
void Board::printCellByPos(char c, int x, int y, int color) {
	gotoxy((y + 1) * BOARD_TAB, HEADER_HEIGHT + (x * 2));
	printCell(string(1, c), color, getBGcellColor(x, y));
}
void Board::resetCellByPos(int x, int y) {
	gotoxy((y + 1) * BOARD_TAB, HEADER_HEIGHT + (x * 2));
	printCell(GetCell(x, y), WHITE, WHITE);
}
int Board::loadFromFile(string filePath, Position* APositions, Position* BPositions)
{
	std::ifstream bfile;
	bfile.open(filePath, ios::in);
	if (bfile.is_open()) {
		std::string str;
		int lineIdx = 0;
		while (std::getline(bfile, str) && lineIdx < _rowSize)
		{
			std::string board_line = str.substr(0, _colSize);
			loadBoardLine(board_line, lineIdx, APositions, BPositions);
			++lineIdx;
		}
	}
	else 
		return errno;

	return 0;
}
void Board::printCell(int cell, int colorA, int colorB)
{
	switch (cell) {

	case FR:
		printCell("^^^^", BLACK, GREEN);
		break;
	case SEA:
		printCell("~~~~", BLACK, CYAN);
		break;
	case FlgA:
		printCell("FlgA", BLACK, BLUE);
		break;
	case FlgB:
		printCell("FlgB", BLACK, RED);
		break;

	case A:
	case B:
	case C:
		printCell(string(1, '0' + cell), colorA);
		break;
	case E:
	case F:
	case G:
		printCell(string(1, '0' + cell), colorB);
		break;

	case EMPTY:
		printCell(" ");
		break;
	}
}
void Board::printBoard(Player* pa, int aColor, Player* pb, int bColor)
{
	cleanBoard();
	printScoreBoard(pa, aColor, pb, bColor);
	printheadline();

	for (int i = 0; i < _rowSize; i++) {
		printCellNumber(to_string(1 + i));
		for (int j = 0; j < _colSize; j++) {
			printCell(boardCells[i][j], aColor, bColor);
		}
		cout << endl;
		printBoardline();
	}

}
char Board::getCharFromWriteLine(string str)
{
	char c;
	int writeLineI = (_rowSize) * 2 + HEADER_HEIGHT;
	clearLine(writeLineI);
	cout << str;
	cin >> c;
	return c;
}