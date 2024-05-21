#pragma once
#include "ChekersBoard.h"

class Player
{
protected:
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
	Player() {};
	virtual ~Player() {};
	void SetupPlayer(std::string name, CellType cellType, CellType dcellType, CellType wcellType);
	void SetBoard(ChekersBoard* board);
	virtual bool MakeMove(int bufdcol, int bufdrow) = 0;
	std::string GetName();
};

