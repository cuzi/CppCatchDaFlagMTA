#pragma once
#include "Board.h"
#include <string>
class Move {
	int _clockTime = -1;
	char _boardTool = -1;
	char _direction = 0;
public:
	Move(int ct, char bt, char d) : _clockTime(ct), _boardTool(bt), _direction(d) {};
	Move() {};
	operator int() const
	{
		return _direction;
	}

	void set(int ct, int bt, char d) {
		_clockTime = ct;
		_boardTool = bt;
		_direction = d;
	}
	int getClockTime() {
		return _clockTime;
	}
	int getTool() {
		return _boardTool;
	}
	int getDir() {
		return _direction;
	}
	static char getPlayerAdir(char d) {
		switch (d)
		{
		case 'U':
			return (char)Direction_A::UP;
		case 'D':
			return (char)Direction_A::DOWN;
		case 'L':
			return (char)Direction_A::LEFT;
		case 'R':
			return (char)Direction_A::RIGHT;
		}
		return -1;
	}
	static char getPlayerEdir(char d) {
		switch (d)
		{
		case 'U':
			return (char)Direction_E::UP;
		case 'D':
			return (char)Direction_E::DOWN;
		case 'L':
			return (char)Direction_E::LEFT;
		case 'R':
			return (char)Direction_E::RIGHT;
		}
		return -1;
	}
	friend std::ostream &operator<<(std::ostream &cout, Move const &m) {
		cout << to_string(m._clockTime) << ',' << to_string(m._boardTool) << ',' << m._direction << endl;
		return cout;
	}
};