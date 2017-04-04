#pragma once
#include <string>
#include <iostream>
#include "Player.h"

using namespace std;

class Menu {
	enum {PICK_NAMES = 1, START_GAME = 2, START_REVERSE_GAME = 3, RESET_SCORE = 4,SHOW_BOARD = 5, EXIT = 9};
	char* txt[9] = { "Pick names", "Start game", "Start reversed game", "Reset score","Show Board","","","", "Exit" };
	Board b = { 13,13 };
	Player pa{&b, "a", RED}, pb{&b, "b", BLUE};

public:
	Menu() {}

	void ShowMenu() {
		int option = 10;
		while (option != EXIT)
		{
			_printMenu();
			cin >> option;
			_triggerAction(option);
		}
		cout << "Bye Bye!\n";
	}

private:
	void _printMenu() {
		cout << "Choose from the following:\n";
		for (int i = 0; i < EXIT; ++i) {
			_printLine(i);
		}
	}
	void _printLine(int i) {
		if (txt[i] != "") {
			cout << "  " << (i + 1) << " - " << txt[i] << endl;
		}
	}
	void _resetScore() {
		pa.setScore(0);
		pb.setScore(0);
	} 
	
	void _pickNames() {
		_pickName(pa);
		_pickName(pb);
	}	
	void _pickName(Player p) {
		string name = "";
		while (name != "") {
			cout << "Enter name to " << p.getName() << endl;
			cin >> name;
		}
		p.setName(name);
	}
	void _triggerAction(int option) {
		switch (option) {
		case PICK_NAMES:
			_pickNames();
			break;
		case START_GAME:
			break;
		case START_REVERSE_GAME:
			break;
		case SHOW_BOARD:
			b.printBoard(pa,pb);
		case RESET_SCORE:
			_resetScore();
			break;
		}
	}
};