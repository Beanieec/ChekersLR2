#include "MonteCarlo.h"

MonteCarlo::MonteCarlo(ChekersBoard* board, int numIterat, CellType startCellType, int dxpos, int dypos, int xpos, int ypos) {
	this->board = board;
	this->numGames = numIterat;
	this->numDraw = 0;
	this->numVictor = 0;
	this->numLose = 0;
	this->dxpos = dxpos;
	this->dypos = dypos;
	this->xpos = xpos;
	this->ypos = ypos;
	this->startCellType = startCellType;
}

void MonteCarlo::EvalutedBoard() {
	ChekersBoard* b = new ChekersBoard(this->board);
	RandPlayer* player1 = new RandPlayer();
	RandPlayer* player2 = new RandPlayer();
	RandPlayer* currentPlayer;
	bool bGameFinished = false;

	player1->SetupPlayer("randWhite", CELLTYPE_PWHITE, CELLTYPE_EBLACK, CELLTYPE_WOMWHITE);
	player2->SetupPlayer("randBlack", CELLTYPE_PBLACK, CELLTYPE_EBLACK, CELLTYPE_WOMBLACK);
	player1->SetBoard(b);
	player2->SetBoard(b);
	currentPlayer = (this->startCellType == CELLTYPE_PWHITE) ? player1 : player2;

	if (b->CheckEndConditionScorecounter()) {
		if (b->CheckEndConditionScorecounter()) {
			if (currentPlayer == player1)
				numVictor++;
			else				
				numLose++;
		}
		else
			numDraw++;
		bGameFinished = true;

		delete player1;
		delete player2;
		delete b;

		return;
	}

	while (!bGameFinished) {
		while (!currentPlayer->MakeMove(0, 0));

		if (b->CheckEndConditionScorecounter()) {
			if (b->CheckEndConditionScorecounter())
				if (currentPlayer == player1)
					numVictor++;
				else
					numLose++;
			else
				numDraw++;
			bGameFinished = true;
		}
		currentPlayer = (currentPlayer == player1) ? player2 : player1;
	}
}

void MonteCarlo::Evaluted() {
	for (int i = 0; i < numGames; i++)
		EvalutedBoard();
}