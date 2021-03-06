#pragma once

#include <iostream>
#include "BoardData.h"

struct GameMove {
	const int from_x, from_y;
	const int to_x, to_y;
	const GameMove(int x1, int y1, int x2, int y2) : from_x(x1), from_y(y1), to_x(x2), to_y(y2) { };
	GameMove& operator=(const GameMove& gm) {
		const_cast<int&>(from_x) = gm.from_x;
		const_cast<int&>(from_y) = gm.from_y;
		const_cast<int&>(to_x) = gm.to_x;
		const_cast<int&>(to_y) = gm.to_y;
		return *this;
	}
};



class AbstractPlayer {
public:
	virtual ~AbstractPlayer() { }
	/* player: 1 for 1-2-3 player, 2 for 7-8-9 */
	virtual void setPlayer(int player) = 0;
	virtual void init(const BoardData& board) = 0;
	virtual GameMove play(const GameMove& opponentsMove) = 0;
	virtual std::string getName() const = 0;
};