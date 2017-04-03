// 203539564 - Tomer Abenheimer
// 203838495 - Ben Fishman

#include "stdafx.h"
#include "Menu.h"
#include "Board.h"
#include "Utils.h"

int main()
{
	Menu menu;
	//menu.ShowMenu();
	Board b = { 13,13 };
	Player pa{ b,"Player A",RED}, pb{ b,"Player B",BLUE};
	b.setBoardCell(3, 3, Board::A);

	b.printBoard(pa,pb);
    return 0;
}

