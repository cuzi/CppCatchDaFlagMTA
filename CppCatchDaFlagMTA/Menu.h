#pragma once

#include <iostream>
#include "Player.h"

using namespace std;

class Menu {
	enum {PICK_NAMES = 1, START_GAME = 2, START_REVERSE_GAME = 3, RESET_SCORE = 4, EXIT = 9};
	Player a{ "a" }, b{ "b" };

public:
	Menu() {}

	void InitGame() {
		cout << "Please pick an option from the menu:\n";
	}

private:
	void _resetScore() {
		a.setScore(0);
		b.setScore(0);
	}

};