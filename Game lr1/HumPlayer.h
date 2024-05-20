#pragma once

#ifndef _TICTACPLAYER_H_

#define _TICTACPLAYER_H_

#include "ChekersBoard.h"
#include "CellType.h"

class HumPlayer {
	ChekersBoard* board;
	CellType cellType;
	CellType dcellType;
	CellType wcellType;
	std::string name;
	char dletter, letter;
	int row, col, drow, dcol;
	int onmorecount = 0;
	int onlyfightcount = 0;
	
public:
	HumPlayer();
	virtual ~HumPlayer();
	void SetupPlayer(std::string name, CellType cellType, CellType dcellType, CellType wcellType);
	void SetBoard(ChekersBoard* board);
	bool MakeMove(int bufdcol, int bufdrow);
	std::string GetName();
};

#endif