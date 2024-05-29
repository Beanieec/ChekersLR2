#pragma once
#include "Player.h"
#include <thread>
class RandPlayer : public Player
{
public:
	RandPlayer() {};
	virtual ~RandPlayer() {};
	virtual bool MakeMove(int bufdcol, int bufdrow);
};

