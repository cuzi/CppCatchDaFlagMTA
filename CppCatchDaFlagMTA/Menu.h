#pragma once
#include <string>
#include <iostream>
#include "Player.h"
#include "Utils.h"
#include "Board.h"
#include "GameManager.h"

using namespace std;

class Menu {
	Board *b;
	GameManager *gm;
	Player *pa, *pb;
	enum { PICK_NAMES = 1, START_GAME = 2, START_REVERSE_GAME = 3, RESET_SCORE = 4, RECORD_GAME = 5, EXIT = 9 };
	char* txt[9] = { "Pick names", "Start game", "Start reversed game", "Reset score","Start record game","","","", "Exit" };

public:
	Menu(Board *board, GameManager *gManager, Player *a, Player *b) : b(board), gm(gManager), pa(a), pb(b) {}

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

	void _pickName(Player *p) {
		string name = "";
		cout << "Enter name to " << p->getName() << endl;
		cin >> name;
		p->setName(name);
	}

	void _printMenu() {
		hideCursor();
		b->cleanBoard();
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
		pa->resetScore();
		pb->resetScore();
	}

	void _triggerAction(int option) {

		switch (option) {
		case PICK_NAMES:
			_pickNames();
			break;
		case START_GAME:
			if (gm->start(pa, pb) == EXIT)
				return;
			break;
		case START_REVERSE_GAME:
			if (gm->start(pb, pa) == EXIT)
				return;
			break;
		case RESET_SCORE:
			_resetScore();
			break;
		case RECORD_GAME:
			(!gm->isRecording()) ? gm->startRecord() : gm->endRecord();
			txt[RECORD_GAME - 1] = (gm->isRecording()) ? "Stop record game" : "Start record game";
			gm->editSubMenu(RECORD_GAME - 1, (gm->isRecording()) ? "Stop record game" : "Start record game");
			break;

		case EXIT:
			cout << "Bye Bye!\n";
			Sleep(500);
			return;

		}
		ShowMenu();
	}
};