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
	void printBoardline()
	{
		for (int i = 0; i <= _rowSize; i++)
			cout << right << setw(BOARD_TAB) << setfill('-') << " ";
		cout << endl;
	}
	void printCell(string str) {
		printCell(str, WHITE);
	}
	int getBGcellColor(int x, int y) {
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
	void printCell(string str, int color, int bgColor) {
		setTextColor(color, bgColor);
		cout << left << setw(BOARD_TAB - 1) << setfill(' ') << str;
		setTextColor(WHITE, BLACK);
		cout << "|";
	}
	void printCell(string str, int color) {
		printCell(str, color, BLACK);
	}
	void printCellNumber(string str) {
		cout << right << setw(BOARD_TAB - 1) << setfill(' ') << str;
		cout << "|";
	}
	void printScoreBoard(Player* pa, int aColor, Player* b, int bColor);
	void printheadline();
	void printCell(int cell, int colorA, int colorB);
	void freeBoardMat();
	string getScoreString(Player* p);
	void loadBoardLine(std::string line, int lineIdx, Position* APositions, Position* BPositions);

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
		}
	}
	const int getBoardWidth() {
		return _colSize;
	}
	const int getBoardHeigth() {
		return _rowSize;
	}
	void clearLine(int line) {
		gotoxy(0, line);
		for (int j = 0; j <= _colSize; j++) {
			cout << setw(BOARD_TAB) << setfill(' ') << " ";
		}

		gotoxy(0, line);
	}
	void cleanBoard() {
		gotoxy(0, 0);
		for (int i = 0; i < _rowSize * 2 + HEADER_HEIGHT; i++) {
			clearLine(i);
		}
		gotoxy(0, 0);
	}
	bool isCellEmpty(int x, int y) {
		return (boardCells[x][y] == EMPTY);
	}
	int GetCell(int x, int y) {
		return boardCells[x][y];
	}
	void setBoardCell(int x, int y, char c) {
		boardCells[x][y] = c;
	}
	void printBoard(Player* pa, int aColor, Player* pb, int bColor);
	char getCharFromWriteLine(string str);
	void printCellByPos(char c, int x, int y, int color);
	void resetCellByPos(int x, int y);
	int loadFromFile(string filePath, Position* APositions, Position* BPositions);
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