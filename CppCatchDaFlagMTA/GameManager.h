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
	GameManager() {
		//s[0].setPoint(Point(10, 10, '@'));
		//s[1].setPoint(Point(70, 10, '#'));
		//s[0].setKeys("wxads");
		//s[1].setKeys("imjlk");
	}
	void run();
};