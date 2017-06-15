#include "AlgorithmPlayer.h"

//AlgorithmRegistration algr{ "203838495",[] {return new AlgorithmPlayer;} }

GameMove AlgorithmPlayer::play(const GameMove& opponentsMove) {
	
	return GameMove(myTools[0].cords.x, myTools[0].cords.y, myTools[0].cords.x, myTools[0].cords.y + 1);

}

void AlgorithmPlayer::init(const BoardData& board) {
	char c;
	for (int i = 0; i < board.cols; ++i) {
		for (int j = 0; j < board.rows; ++j) {
			c = board.charAt(i, j);
			switch (c) {
			case '#':
				setAnemy(i, j);
				break;
			case 'A':
				(playerKey == 1 ? MyFlag : targetFlag).x = i;
				(playerKey == 1 ? MyFlag : targetFlag).y = j;
				break;
			case 'B':
				(playerKey == 2 ? MyFlag : targetFlag).x = i;
				(playerKey == 2 ? MyFlag : targetFlag).y = j;
				break;
			case SEA:
			case FR:
				this->board[i][j] = c;
				break;
			case '1':
			case '7':
				setMyTool(0, 1, c, i, j);
				break;
			case '2':
			case '8':
				setMyTool(1, 2, c, i, j);
				break;
			case '3':
			case '9':
				setMyTool(2, 3, c, i, j);
				break;
			}
		}
	}

};