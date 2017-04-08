#pragma once

#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include "stdafx.h"
#include "Utils.h"
#include "Player.h"

using namespace std;

class Player;

class Board {
	
	//Data members
	int _rowSize;;
	int _colSize;
	const int BOARD_TAB = 5;
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

	void printCell(string str, int color) {
		setTextColor(color);
		cout << left << setw(BOARD_TAB - 1) << setfill(' ') << str;
		setTextColor(WHITE);
		cout << "|";
	}
	void printCellNumber(string str) {
		cout << right << setw(BOARD_TAB - 1) << setfill(' ') << str;
		cout << "|";
	}
	void printScoreBoard(Player pa, Player pb);
	void printheadline(Player pa, Player pb);
	void printCell(int cell, int colorA, int colorB);
	void configBoardCells();
	string getScoreString(Player p);
		
public:
	enum { FR = 0, SEA = 1, FlgA = 2, FlgB = 3, EMPTY = 4, A = 5, B = 6, C = 7, E = 8, F = 9, G = 10 };

	Board(int rowSize, int colSize) : _rowSize(rowSize), _colSize(colSize) {
		boardCells = new int*[rowSize];
		for (int i = 0; i < rowSize; ++i) {
			boardCells[i] = new int[colSize];
			for (int j = 0; j < colSize; ++j)
				boardCells[i][j] = EMPTY;
		}
		Board::configBoardCells();
	}

	int getBoardWidth() {
		return _colSize;
	}

	int getBoardHeigth() {
		return _rowSize;
	}
	void cleanBoard() {
		gotoxy(0, 0);
		for (int i = 0; i < _rowSize; i++) {
			for (int j = 0; j < _colSize; j++) {
				cout << setw(BOARD_TAB) << " ";
			}
			cout << "\n";
		}
		gotoxy(0, 0);		
	}

	bool isCellEmpty(int x, int y) {
		return (boardCells[x][y] == EMPTY);
	}

	void setBoardCell(int x, int y, char c) {
		boardCells[x][y] = c;
	}

	void printBoard(Player a, Player b);
};