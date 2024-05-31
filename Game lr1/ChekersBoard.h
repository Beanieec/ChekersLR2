#pragma once

#ifndef _TICTACBOARD_H_

#define _TICTACBOARD_H_
#include <algorithm>
#include <random>
#include <iostream>
#include <cmath>
#include <vector>
#include <functional>
#include "CellType.h"

class ChekersBoard {
	int boardsize;
	CellType** cells;
	bool side = false;
	std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> sCheck;
	std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> fCheck;
public:
	ChekersBoard(int size);
	ChekersBoard(ChekersBoard* board);
	virtual ~ChekersBoard();
	void Show();
	void SetCell(CellType ct, int xpos, int ypos, int dxpos, int dypos, CellType dct);
	void SetCell(int xpos, int ypos, CellType wct, int dxpos, int dypos, CellType dct);
	
	void HodProverka(int dxpos, int dypos, CellType ct, std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>* SimpCor);
	void FightProverka(int dypos, int dxpos, CellType ct, std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>* fightCor);
	void SimpleStep(CellType ct, std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>* SimplCor);
	void FightStep(CellType ct, std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>* SimplCor);

	bool CheckLegal(int xpos, int ypos, int bufxpos, int bufypos, int dxpos, int dypos, CellType ct);
	bool CheckLegal(int xpos, int ypos, int dxpos, int dypos, CellType ct, CellType wct);
	bool MovesRule(int xpos, int ypos, int dxpos, int dypos, CellType ct, CellType wct);
	bool iisWoman(int dxpos, int dypos);
	bool Woman(int ypos, CellType ct);
	
	void CanFight(std::vector<std::pair<std::pair<int, int>, bool>>* canfightCoords, int dypos, int dxpos, CellType ct);
	void CanFightOneMore(std::vector<std::pair<std::pair<int, int>, bool>>* canfightonemoreCoordsint, int dypos, int dxpos, CellType ct);
	bool OneMore(int xpos, int ypos, int dxpos, int dypos, CellType ct);
	bool onlyFight(CellType ct);
	void onlyFightcheck(CellType ct, std::vector<std::pair<std::pair<int, int>, bool>>* validCoords);
	bool onlyFightRule(int xpos, int ypos, int dxpos, int dypos, CellType ct);
	bool CheckEndConditionScorecounter();
};

#endif