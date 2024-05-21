#pragma once
#include "Player.h"
class BotPlayer :public Player
{
public:
	BotPlayer() {};
	virtual ~BotPlayer() {};
	virtual bool MakeMove(int bufdcol, int bufdrow);
};

