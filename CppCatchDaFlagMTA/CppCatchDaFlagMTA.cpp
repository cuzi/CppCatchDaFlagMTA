// 203539564 - Tomer Abenheimer
//

#include "stdafx.h"
#include "Menu.h"

int main()
{
	Menu menu;
	menu.ShowMenu();
	Board b = { 13,13 };
	b.configBoardCells();
	b.printBoard();
    return 0;
}

