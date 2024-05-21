#pragma once

#ifndef _TICTACPLAYER_H_

#define _TICTACPLAYER_H_

#include "Player.h"
#include "ChekersBoard.h"
#include "CellType.h"

class HumPlayer : public Player{	
public:
	HumPlayer() {};
	virtual ~HumPlayer() {};
	virtual bool MakeMove(int bufdcol, int bufdrow);
};

#endif