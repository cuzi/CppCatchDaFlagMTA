#pragma once

#include "stdafx.h"
#include "Board.h"
#include "Player.h"
#include "GameManager.h"
#include "Menu.h"
#include <Windows.h>
#include <io.h> 

using namespace std;

static const string BOARD_EXT = "gboard", MOVES_A_EXT = "moves-a", MOVES_B_EXT = "moves-b";

class Game {
	static const int BOARD_SIZE = 13;
	Board b = Board(BOARD_SIZE, BOARD_SIZE, false);
	GameManager gm{ &b };
	string _path;
	Player pa{ "Player A" }, pb{ "Player B" };
	Menu menu{ &b, &gm, &pa, &pb };

public:
	Game(string path) : _path(path) {
		gm.setGamePath(path);
	}
	void setQuiet(bool quiet) {
		gm.setQuiet(quiet);
	}

	void setPath(string path) {
		_path = path;
		gm.setGamePath(path);
	}
	void setDelay(int delay) {
		gm.setDelay(delay);
	}
	void start() {
		menu.ShowMenu();
	}

	void startBoard() {

		string boardPath;

		gm.setBoard(boardPath);
		start();
	}
	void startAuto(char moves_type) {

		vector<string> boardPaths = getSortedFilesByType(BOARD_EXT);
		string playerAmoves, playerBmoves, boardName;
		bool valid = true;

		for (vector<string>::size_type i = 0; i != boardPaths.size() && valid; i++) {
			boardName = getFileName(boardPaths[i]);

			playerAmoves = pathBuilder({ boardName + "." + MOVES_A_EXT });
			playerBmoves = pathBuilder({ boardName + "." + MOVES_B_EXT });

			gm.setBoard(pathBuilder({ boardPaths[i] }));
			if (moves_type == 'f') {
				gm.setMoves(isFileExists(playerAmoves) ? playerAmoves : "",
					isFileExists(playerBmoves) ? playerBmoves : "");
			}
			else {
				// TODO: add moves from algo
			}
			valid = gm.start(&pa, &pb) == 1;
		}

		printSum();
	}
private: 
	string getFileName(string filePath) {
		return filePath.substr(0, filePath.find_last_of("."));
	}
	string pathBuilder(vector<string> dirs) {
		string path = _path;
		for (auto const& d : dirs) {
			path += "\\" + d;
		}
		return path;
	}


	void printSum() {
		b.cleanBoard();
		cout << "Game Summary\nA points : " << pa.getScore() << endl;
		cout << "B points : " << pb.getScore() << endl;
		Sleep(1250);

	}
	vector<string> getSortedFilesByType(string type)
	{
		vector<string> files;
		string search_path = _path + "\\*." + type;
		WIN32_FIND_DATA fd;
		HANDLE hFind = FindFirstFile(search_path.c_str(), &fd);
		if (hFind != INVALID_HANDLE_VALUE) {
			do {
				if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
					files.push_back(fd.cFileName);
				}
			} while (FindNextFile(hFind, &fd));
			FindClose(hFind);
		}
		return files;
	}

	bool isFileExists(const std::string &Filename)
	{
		return _access_s(Filename.c_str(), 0) == 0;
	}
};