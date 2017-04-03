#include "stdafx.h"
#include "Board.h"
#include <iostream>
#include <iomanip>
using namespace std;
#include <vector>
#include "Utils.h"
#include <string.h>

void Board::printBoardline()
{
	for (int i = 0; i < _rowSize; i++) {

		cout << setw(BOARD_TAB) << "----";
	}
	cout << endl;
}

void Board::printhedline()
{
	char rowIdx = 'a';

	gotoxy(BOARD_TAB - 1, 0);
	setTextColor(BLUE);
	cout << "A:" << "0";
	gotoxy(_colSize*BOARD_TAB, 0);
	setTextColor(RED);
	cout << "B:" << "0";
	setTextColor(WHITE);

	gotoxy(BOARD_TAB, 1);

	for (int i = 0; i < _colSize; i++) {
		cout << " " << (char)(rowIdx + i) << setw(BOARD_TAB - 1);
	}
}

void Board::configBoardCells()
{
	boardCells[6][0] = FR;
	boardCells[7][0] = FR;
	boardCells[3][2] = FR;
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

void Board::printCell(int cell)
{
	switch (cell) {

	case FR:
		cout << "FR" << setw(BOARD_TAB - 2) << "|";
		break;

	case SEA:
		cout << "SEA" << setw(BOARD_TAB - 3) << "|";
		break;
	case FlgA:
		cout << "FlgA" << setw(BOARD_TAB - 4) << "|";
		break;

	case FlgB:
		cout << "FlgB" << setw(BOARD_TAB - 4) << "|";
		break;

	case EMPTY:
		cout << setw(BOARD_TAB) << "|";
		break;
	}
}

void Board::printBoard()
{
	Board::printhedline();
	cout << setw(2) << endl << "   ";
	Board::printBoardline();

	for (int i = 0; i < _rowSize; i++) {
		// print the first character as part of the opener.
		cout << setw(2) << i + 1 << setw(2) << "|";
		for (int j = 0; j < _colSize - 1; j++) {
			// only add spaces for subsequent characters.
			Board::printCell(boardCells[i][j]);
		}
		cout << setw(BOARD_TAB) << "|" << setw(2) << endl << "   ";
		Board::printBoardline();
	}
}
