#pragma once
#include <iostream>
#include <string>


using namespace std;

class Board {
	//Data members
	enum { FR = 0, SEA = 1, FlgA = 2, FlgB=3 ,EMPTY=4};
	int _rowSize;;
	int _colSize;
	const int BOARD_TAB = 5;
	int** boardCells;
	//Private Functions
	void printBoardline();
	void printhedline();
	void printCell(int cell);
		
public:
	Board(int rowSize, int colSize) : _rowSize(rowSize), _colSize(colSize) {
		boardCells = new int*[rowSize];
		for (int i = 0; i < rowSize; ++i) {
			boardCells[i] = new int[colSize];
			for (int j = 0; j < colSize; ++j)
				boardCells[i][j] = EMPTY;
		}	
	}
	void configBoardCells();

	void printBoard();

};