#pragma once
#include <string>
#include <iostream>
#include "Player.h"
#include "GameManager.h"

using namespace std;

class Menu {
	enum {PICK_NAMES = 1, START_GAME = 2, START_REVERSE_GAME = 3, RESET_SCORE = 4, EXIT = 9};
	char* txt[9] = { "Pick names", "Start game", "Start reversed game", "Reset score","","","","", "Exit" };
	Board b = { 13,13 };
	GameManager gm{&b};
	Player pa{&b, "Player A",Player::A, RED}, pb{&b, "Player B",Player::E, BLUE};

public:
	Menu() {}

	void ShowMenu() {
		int option;
		_printMenu();
		cin >> option;
		_triggerAction(option);
	}

private:
	void _pickNames() {
		_pickName(pa);
		_pickName(pb);
	}

	void _pickName(Player &p) {
		string name = "";
		cout << "Enter name to " << p.getName() << endl;
		cin >> name;
		p.setName(name);
	}

	void _printMenu() {
		b.cleanBoard();
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
	
	void _triggerAction(int option) {
		switch (option) {
		case PICK_NAMES:
			_pickNames();
			break;
		case START_GAME:
			gm.start(pa, pb);
			break;
		case START_REVERSE_GAME:
			gm.start(pb, pa);
			break;
		case RESET_SCORE:
			_resetScore();
			break;
		case EXIT:
			cout << "Bye Bye!\n";
			exit(0);
		}
		ShowMenu();
	}
};