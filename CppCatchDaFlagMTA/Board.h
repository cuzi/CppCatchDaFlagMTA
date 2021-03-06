#pragma once

#include <string>
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <vector>
#include <fstream>
#include "stdafx.h"
#include "Utils.h"
#include "Player.h"
#include "Position.h"
#include "BoardData.h"

using namespace std;

class Player;

class Board {

	//Data members
	int _rowSize;;
	int _colSize;
	const int BOARD_TAB = 5;
	const int HEADER_HEIGHT = 3;
	int** boardCells;

	//Private Functions
	void printBoardline() const
	{
		for (int i = 0; i <= _rowSize; i++)
			cout << right << setw(BOARD_TAB) << setfill('-') << " ";
		cout << endl;
	}
	void printCell(string str) const {
		printCell(str, WHITE);
	}
	int getBGcellColor(int x, int y) const {
		int cell = GetCell(x, y);

		switch (cell)
		{
		case SEA:
			return CYAN;
		case FR:
			return GREEN;
		default:
			return BLACK;
		}
	}
	void printCell(string str, int color, int bgColor)  const {
		setTextColor(color, bgColor);
		cout << left << setw(BOARD_TAB - 1) << setfill(' ') << str;
		setTextColor(WHITE, BLACK);
		cout << "|";
	}
	void printCell(string str, int color) const {
		printCell(str, color, BLACK);
	}
	void printCellNumber(string str)  const {
		cout << right << setw(BOARD_TAB - 1) << setfill(' ') << str;
		cout << "|";
	}
	void printScoreBoard(Player* pa, int aColor, Player* b, int bColor) const;
	void printheadline() const;
	void printCell(int cell, int colorA, int colorB) const;
	void freeBoardMat();
	string getScoreString(Player* p) const;

public:
	enum { FR = 4, SEA = 5, FlgA = 6, FlgB = 10, EMPTY = 0, A = 1, B = 2, C = 3, E = 7, F = 8, G = 9 };

	Board(int rowSize, int colSize, bool is_random = true) : _rowSize(rowSize), _colSize(colSize) {
		boardCells = new int*[rowSize];
		for (int i = 0; i < rowSize; ++i) {
			boardCells[i] = new int[colSize];
			for (int j = 0; j < colSize; ++j)
				boardCells[i][j] = EMPTY;
		}
		if (is_random)
			Board::configRandBoardCells();
	}
	Board(const Board &b2) {
		_rowSize = b2._rowSize;
		_colSize = b2._colSize;
		freeBoardMat();
		boardCells = b2.boardCells;
	}
	Board& operator=(const Board& other) {
		_rowSize = other._rowSize;
		_colSize = other._colSize;
		freeBoardMat();
		boardCells = other.boardCells;
		return *this;
	}
	~Board() { freeBoardMat(); };
	void configRandBoardCells();
	void initBoard() {
		for (int i = 0; i < _rowSize; ++i) {
			for (int j = 0; j < _colSize; ++j)
				boardCells[i][j] = EMPTY;
		}
	}
	int ** const &getBoard() { 
		return boardCells; 
	}
	static char getBoardChar(int key) {
		switch (key)
		{
		case FR:
			return 'T';
		case SEA:
			return 'S';
		case EMPTY:
			return ' ';
		case FlgA:
			return 'A';
		case FlgB:
			return 'B';
		case A:
			return '1';
		case B:
			return '2';
		case C:
			return '3';
		case E:
			return '7';
		case F:
			return '8';
		case G:
			return '9';
		default:
			return ' ';
		}
	}
	static char getBoardKey(char key) {
		switch (key)
		{
		case 'T':
			return FR;
		case 'S':
			return SEA;
		case ' ':
			return EMPTY;
		case 'A':
			return FlgA;
		case 'B':
			return FlgB;
		case '1':
			return A;
		case '2':
			return B;
		case '3':
			return C;
		case '7':
			return E;
		case '8':
			return F;
		case '9':
			return G;
		default:
			return ' ';
		}
	}

	const int getBoardWidth() {
		return _colSize;
	}
	const int getBoardHeigth() {
		return _rowSize;
	}
	void clearLine(int line) const {
		gotoxy(0, line);
		for (int j = 0; j <= _colSize; j++) {
			cout << setw(BOARD_TAB) << setfill(' ') << " ";
		}

		gotoxy(0, line);
	}
	void cleanBoard()  const {
		gotoxy(0, 0);
		for (int i = 0; i < _rowSize * 2 + HEADER_HEIGHT; i++) {
			clearLine(i);
		}
		gotoxy(0, 0);
	}
	bool isCellEmpty(int x, int y) const {
		return (boardCells[x][y] == EMPTY);
	}
	int GetCell(int x, int y) const  {
		return boardCells[x][y];
	}
	void setBoardCell(int x, int y, char c) {
		boardCells[x][y] = c;
	}
	void printBoard(Player* pa, int aColor, Player* pb, int bColor) const;
	char getCharFromWriteLine(string str) const;
	void printCellByPos(char c, int x, int y, int color) const;
	void resetCellByPos(int x, int y);
	friend std::ostream &operator<<(std::ostream &cout, Board const &b) {
		for (int i = 0;i<b._colSize;i++) {
			for (int j = 0;j < b._rowSize;j++) {
				cout << Board::getBoardChar(b.boardCells[i][j]);
			}
			cout << "# " << to_string(i + 1) << endl;
		}
		cout << "-------------" << endl;
		cout << "ABCDEFGHIJKLM" << endl;
		return cout;
	}
};