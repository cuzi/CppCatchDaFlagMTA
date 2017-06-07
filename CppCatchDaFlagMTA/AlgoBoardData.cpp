#include "AlgoBoardData.h"

int  AlgoBoardData::searchInTools(int x, int y) const {

	for (int i = 0;i < TOOLS_COUNT;i++) {
		if (x == btPa[i].getX() && y == btPa[i].getY())
			return btPa[i].getC() - '0';
		if (x == btPb[i].getX() && y == btPb[i].getY())
			return btPb[i].getC() - '0';
	}
	return -1;
}