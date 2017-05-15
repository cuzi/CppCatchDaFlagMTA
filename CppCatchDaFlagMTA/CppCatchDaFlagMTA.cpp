// 203539564 - Tomer Abenheimer
// 203838495 - Ben Fishman 

#include "stdafx.h"
#include "Game.h"
#include "Utils.h"
#include <cmath>
#include <functional>
#include <map>


int main(int argSize, char *argv[]) {
	string argv_str(argv[0]);
	string basePath = argv_str.substr(0, argv_str.find_last_of("\\"));

	Game game { basePath };
	bool moves = false, board = false, quiet = false;
    auto parameters = std::map<std::string,std::function<void (int*)>> {
		{"-path",   [&](int *i) {
			(*i)++;

			string path = *(argv + *i);

			if (path[0] == '.')
				path = basePath + path.substr(1, path.size());

			game.setPath(path);
		}},
        {"-delay",  [&]( int *i ) { (*i)++; game.setDelay((int)*(argv + *i)); }},
        {"-moves",  [&]( int *i ) { (*i)++; moves = ! strcmp( "f", *(argv + *i)); }},
        {"-board",  [&]( int *i ) { (*i)++; board = ! strcmp( "f", *(argv + *i)); }},
		{"-quiet",  [&](int *i) { quiet = true; }}
    };

	for (int i = 1; i < argSize; ++i) 
		parameters[argv[i]](&i);


	if (moves && board) {
		if (quiet)
			game.setQuiet(quiet);
		game.startAuto();
	}

	else if (moves && board) 
		game.startBoard();

	else game.start();


	return 0;
}