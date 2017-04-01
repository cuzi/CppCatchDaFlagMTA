#pragma once
#include <iostream>
#include <string.h>


using namespace std;

class Player {
	string _name;
	int _score;

public:
	Player(string name) : _name(name), _score(0) {}
};