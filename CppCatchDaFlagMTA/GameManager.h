#pragma once

#include <Windows.h>
#include <conio.h>
#include "stdafx.h"
#include "Board.h"
#include "BoardTool.h"

class GameManager {
	enum { ESC = 27 };
	Board* _b;
public:
	GameManager(Board * b) : _b(b) {}
	void start(Player a, Player b);
};