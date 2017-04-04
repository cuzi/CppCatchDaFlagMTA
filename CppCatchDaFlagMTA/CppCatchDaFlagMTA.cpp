// 203539564 - Tomer Abenheimer
// 203838495 - Ben Fishman = 0

#include "stdafx.h"
#include "Menu.h"
#include "Board.h"
#include "Utils.h"

int main()
{
	Menu menu;
	//menu.ShowMenu();
	Board b = { 13,13 };
	Player pa{ &b,"Player A",Player::A,RED }, pb{ &b,"Player B", Player::E, BLUE };
	b.printBoard(pa,pb);
    return 0;
}

