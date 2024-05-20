#pragma once

#ifndef _TICTACMANAGER_H_

#define _TICTACMANAGER_H_

#include <iostream>
#include <string>
#include "ChekersBoard.h"
#include "HumPlayer.h"
#include "CellType.h"

using namespace std;

class GameManager {
	ChekersBoard* board;
	HumPlayer* player1;
	HumPlayer* player2;
	HumPlayer* currentPlayer;
	bool bGameFinished = false;
public:
	GameManager();
	virtual ~GameManager();
	bool Init();
	void ShowBoard();
	void MakeMove();
	bool IsGameFinished();
private:
	string wh = "\033[31;42m()\033[0m";
	string bk = "\033[37;42m()\033[0m";
	string kwh = "\033[31;42m[]\033[0m";
	string kbk = "\033[37;42m[]\033[0m";
};

#endif