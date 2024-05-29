#pragma once
#include "ChekersBoard.h"
#include "RandPlayer.h"

class MonteCarlo
{
private:
	ChekersBoard* board;
	int numGames;
	int numVictor;
	int numLose;
	int numDraw;
	int dxpos, dypos, xpos, ypos;
	CellType startCellType;
public:
	MonteCarlo(ChekersBoard* board, int numIterat, CellType startCellType, int dxpos, int dypos, int xpos, int ypos);
	virtual ~MonteCarlo() {}
	void EvalutedBoard();
	void Evaluted();
	int GetVictor() { return numVictor; }
	int GetLose() { return numLose; }
	int dGetXpos() { return dxpos; }
	int dGetYpos() { return dypos; }
	int GetXpos() { return xpos; }
	int GetYpos() { return ypos; }
};

