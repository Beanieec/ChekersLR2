#pragma once
#include "ChekersBoard.h"

class MonteCarlo
{
private:
	ChekersBoard* board;
	int numGames;
	int numVictor;
	int numLose;
	int numDraw;
	int xpos, ypos;
	CellType startCellType;
public:
	MonteCarlo(ChekersBoard* board, int numIterat, CellType startCellType, int xpos, int ypos);
	~MonteCarlo();
};

