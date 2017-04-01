#include "stdafx.h"
#include "Board.h"
#include <iostream>
#include <iomanip>
using namespace std;
#include <vector>
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

	cout << setw(2) << "  ";
	for (int i = 0; i < _colSize; i++) {

		cout << setw(BOARD_TAB) << (char)(rowIdx + i);
	}
}

void Board::configBoardCells()
{
	boardCells[3][2] = FR;
}

void Board::printCell(int cell)
{
	switch (cell) {

	case FR:
			cout << setw(BOARD_TAB) << "FR" << "|";
			break;

	case SEA:
			cout << setw(BOARD_TAB) << "SEA" << "|";
			break;
	case FlgA:
		cout << setw(BOARD_TAB) << "FlgA" << "|";
		break;

	case FlgB:
		cout << setw(BOARD_TAB) << "FlgB" << "|";
		break;

	case EMPTY:
		cout << setw(BOARD_TAB) << "|";
		break;
	}
}

void Board::printBoard()
{
	Board::printhedline();
	cout << setw(2)  << endl << "   ";
	Board::printBoardline();

	for (int i = 0; i < _rowSize; i++) {
		// print the first character as part of the opener.
		cout << setw(2) << i + 1 << setw(2) << "|";
		for (int j = 1; j < _colSize; j++) {
			// only add spaces for subsequent characters.
			Board::printCell(boardCells[i][j]);
		}
		cout << setw(BOARD_TAB) << "|" << setw(2) << endl << "   ";
		Board::printBoardline();
	}
}
