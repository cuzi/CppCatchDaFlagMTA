#pragma once
#include <iostream>
#include <string.h>


using namespace std;

class Player {
	string _name;
	int _score;

public:
	Player(string name) : _name(name), _score(0) {}
	void setScore(int score) {
		_score = score;
	}
	void setName(string name) {
		_name = name;
	}
	string getName() {
		return _name;
	}
};