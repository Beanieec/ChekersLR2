#include "MonteCarlo.h"

MonteCarlo::MonteCarlo(ChekersBoard* board, int numIterat, CellType startCellType, int xpos, int ypos) {
	this->board = board;
	this->numGames = numIterat;
	this->numDraw = 0;
	this->numVictor = 0;
	this->numLose = 0;
	this->xpos = xpos;
	this->ypos = ypos;
	this->startCellType = startCellType;
}