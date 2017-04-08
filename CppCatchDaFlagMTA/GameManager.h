#pragma once

#include <Windows.h>
#include <conio.h>
#include "stdafx.h"
#include "BoardTool.h"

class GameManager {
	enum { ESC = 27 };
	//Snake s[2];
	BoardTool starToEat{ 5,5 };
public:
	GameManager() {}
	void run();
};