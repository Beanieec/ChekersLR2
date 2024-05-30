#include "ChekersBoard.h"

ChekersBoard::ChekersBoard(int size) {
	this->boardsize = size;
	this->cells = new CellType * [size];
	for (int i = 0; i < size; i++) {
			cells[i] = new CellType[size];
		for (int j = 1; j < boardsize; j ++){
			if ((i + j) % 2 == 0) {
				cells[i][j] = CELLTYPE_EWHITE;
			}
			else
				cells[i][j] = CELLTYPE_EBLACK;
		}
		if (boardsize > 8) {
			if (i % 2 == 1 && i <= 3) {
				for (int j = 2; j <= 8; j += 2) {
					cells[i][j] = CELLTYPE_PWHITE;
				}
			}
			if (i == 2) {
				for (int j = 1; j <= 8; j += 2) {
					cells[i][j] = CELLTYPE_PWHITE;
				}
			}

			if (i % 2 == 0 && i == 6 || i == 8) {
				for (int j = 1; j <= 8; j += 2) {
					cells[i][j] = CELLTYPE_PBLACK;
				}
			}
			if (i == 7) {
				for (int j = 2; j <= 8; j += 2) {
					cells[i][j] = CELLTYPE_PBLACK;
				}
			}
		}
	}
	/*cells[7][4] = CELLTYPE_WOMWHITE;
	cells[6][5] = CELLTYPE_WOMWHITE;
	cells[7][2] = CELLTYPE_WOMWHITE;
	cells[3][2] = CELLTYPE_WOMWHITE;
	cells[4][7] = CELLTYPE_WOMBLACK;*/
}

ChekersBoard::ChekersBoard(ChekersBoard* board) {
	this->boardsize = board->boardsize;
	this->cells = new CellType * [boardsize];
	for (int i = 0; i < boardsize; i++) {
		cells[i] = new CellType[boardsize];
		for (int j = 1; j < boardsize; j++) {
			if ((i + j) % 2 == 0) {
				cells[i][j] = CELLTYPE_EWHITE;
			}
			else
				cells[i][j] = CELLTYPE_EBLACK;
		}
	}
}

void ChekersBoard::Show() {
	std::cout << "        ";
	std::cout << "\033[30;43m  \033[0m";
	for (int j = 1; j < boardsize; j++) {
		if (j > 9) {
			std::cout << j;
		}
		else
			std::cout << "\033[4;30;43m " << j << "\033[0m";
	}
	std::cout << "\033[30;43m  \033[0m" << std::endl;
	for (int i = 1; i < boardsize; i++) {
		char abc[27];
		abc[i] = '@' + i;
		std::cout << "        \033[30;43m " << abc[i] << "\033[0m";
		for (int j = 0; j < boardsize; j++) {
			switch (cells[i][j]) {
			case CELLTYPE_PBLACK:
				std::cout << "\033[31;42m()\033[0m";
				break;
			case CELLTYPE_PWHITE:
				std::cout << "\033[37;42m()\033[0m";
				break;
			case CELLTYPE_EBLACK:
				std::cout << "\033[42m  \033[0m";
				break;
			case CELLTYPE_EWHITE:
				std::cout << "\033[47m  \033[0m";
				break;
			case CELLTYPE_WOMBLACK:
				std::cout << "\033[31;42m[]\033[0m";
				break;
			case CELLTYPE_WOMWHITE:
				std::cout << "\033[37;42m[]\033[0m";
				break;
			}
		}
		std::cout << "\033[30;43m" << abc[i] << " \033[0m" << std::endl;
	}
	std::cout << "        \033[4;30;43m  \033[0m";
	for (int j = 1; j < boardsize; j++) {
		if (j > 9) {
			std::cout << j;
		}
		else
			std::cout << "\033[4;30;43m" << j << " \033[0m";
	}
	std::cout << "\033[4;30;43m  \033[0m" << std::endl;
}

void ChekersBoard::SetCell(int xpos, int ypos, CellType wct, int dxpos, int dypos, CellType dct) { //отрисовка хода дамки
		cells[ypos][xpos] = wct;
		cells[dypos][dxpos] = dct;
}

void ChekersBoard::SetCell(CellType ct, int xpos, int ypos, int dxpos, int dypos, CellType dct) { //отрисовка хода пешки
		cells[ypos][xpos] = ct;
		cells[dypos][dxpos] = dct;
}

ChekersBoard::~ChekersBoard() {
	for (int i = 0; i < boardsize; i++)
		delete[] cells[i];
	delete[] cells;
	sC.shrink_to_fit();
	fC.shrink_to_fit();
}

bool ChekersBoard::CheckLegal(int xpos, int ypos, int bufxpos, int bufypos, int dxpos, int dypos, CellType ct) { //ONLYFIGHTEDIT
	if (bufxpos != dxpos || bufypos != dypos) {
		return false;
	}
	return true;
} 

bool ChekersBoard::CheckLegal(int xpos, int ypos, int dxpos, int dypos, CellType ct, CellType wct) { //базовые условия
	if ((xpos < 0) || (xpos >= boardsize) || (ypos < 0) || (ypos >= boardsize))
		return false;
	if (cells[dypos][dxpos] == CELLTYPE_EBLACK)
		return false;
	if (cells[dypos][dxpos] == CELLTYPE_EWHITE)
		return false;
	if (cells[ypos][xpos] == CELLTYPE_EWHITE)
		return false;
	if (!MovesRule(xpos, ypos, dxpos, dypos, ct, wct))
		return false;
	return (cells[ypos][xpos] == CELLTYPE_EBLACK);
}
 
void ChekersBoard::SimpleStep(CellType ct, std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>* SimplCor){
	sC.clear();
	sC.shrink_to_fit();
	for (int i = 1; i < boardsize; i++) {
		for (int j = 0; j < boardsize; j++) {
			HodProverka(j, i, ct, &sC);

			std::random_device rd;
			std::mt19937 g(rd());
			std::shuffle(sC.begin(), sC.end(), g);

			for (const auto& coord : sC) {
				int dx = coord.first.first;
				int dy = coord.first.second;
				int kx = coord.second.first;
				int ky = coord.second.second;
				SimplCor->push_back(std::make_pair(std::make_pair(dx, dy), std::make_pair(kx, ky)));
			}
		}
	}
}

void ChekersBoard::FightStep(CellType ct, std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>* FightCor) {
	fC.clear();
	fC.shrink_to_fit();
	for (int i = 1; i < boardsize; i++) {
		for (int j = 0; j < boardsize; j++) {
			FightProverka(j, i, ct, &fC);

			for (const auto& coord : fC) {
				int dx = coord.first.first;
				int dy = coord.first.second;
				int kx = coord.second.first;
				int ky = coord.second.second;
				FightCor->push_back(std::make_pair(std::make_pair(dx, dy), std::make_pair(kx, ky)));
			}
		}
	}
}

void ChekersBoard::HodProverka(int dxpos, int dypos, CellType ct, std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> *SimpCor) {

	switch (ct)
	{
	case CELLTYPE_PWHITE:
		if (cells[dypos][dxpos] == CELLTYPE_WOMWHITE) {
			if (dypos != 1) {
				if (cells[dypos - 1][dxpos + 1] == CELLTYPE_EBLACK) {
					SimpCor->push_back(std::make_pair(std::make_pair(dypos, dxpos), std::make_pair(dypos - 1, dxpos + 1)));
				}
				if (cells[dypos - 1][dxpos - 1] == CELLTYPE_EBLACK) {
					SimpCor->push_back(std::make_pair(std::make_pair(dypos, dxpos), std::make_pair(dypos - 1, dxpos - 1)));
				}
			}
		}
		if (dypos + 1 >= boardsize) {
			return;
		}
		if (cells[dypos + 1][dxpos + 1] == CELLTYPE_EBLACK) {
			if (cells[dypos][dxpos] == CELLTYPE_PWHITE || cells[dypos][dxpos] == CELLTYPE_WOMWHITE) {
				SimpCor->push_back(std::make_pair(std::make_pair(dypos, dxpos), std::make_pair(dypos + 1, dxpos + 1)));
			}
		}
		if (cells[dypos + 1][dxpos - 1] == CELLTYPE_EBLACK) {
			if (cells[dypos][dxpos] == CELLTYPE_PWHITE || cells[dypos][dxpos] == CELLTYPE_WOMWHITE) {
				SimpCor->push_back(std::make_pair(std::make_pair(dypos, dxpos), std::make_pair(dypos + 1, dxpos - 1)));
			}
		}
		break;

	case CELLTYPE_PBLACK:	
		if (cells[dypos][dxpos] == CELLTYPE_WOMBLACK) {
			if (cells[dypos + 1][dxpos + 1] == CELLTYPE_EBLACK) {
				SimpCor->push_back(std::make_pair(std::make_pair(dypos, dxpos), std::make_pair(dypos + 1, dxpos + 1)));
			}
			if (cells[dypos + 1][dxpos - 1] == CELLTYPE_EBLACK) {
				SimpCor->push_back(std::make_pair(std::make_pair(dypos, dxpos), std::make_pair(dypos + 1, dxpos - 1)));
			}
		}
		if (dypos - 1 <= 0) {
			return;
		}
		if (cells[dypos - 1][dxpos + 1] == CELLTYPE_EBLACK) {
			if (cells[dypos][dxpos] == CELLTYPE_PBLACK || cells[dypos][dxpos] == CELLTYPE_WOMBLACK) {
				SimpCor->push_back(std::make_pair(std::make_pair(dypos, dxpos), std::make_pair(dypos - 1, dxpos + 1)));
			}
		}
		if (cells[dypos - 1][dxpos - 1] == CELLTYPE_EBLACK) {
			if (cells[dypos][dxpos] == CELLTYPE_PBLACK || cells[dypos][dxpos] == CELLTYPE_WOMBLACK) {
				SimpCor->push_back(std::make_pair(std::make_pair(dypos, dxpos), std::make_pair(dypos - 1, dxpos - 1)));
			}
		}
		break;
	}
}

void ChekersBoard::FightProverka(int dypos, int dxpos, CellType ct, std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>* fightCor) {
	std::vector<std::pair<std::pair<int, int>, bool>> canfightmoreCoords;
	switch (ct)
	{
	case CELLTYPE_PWHITE://белые
		if ((cells[dypos][dxpos]) == CELLTYPE_WOMWHITE) { //Дамка
			if ((cells[dypos - 1][dxpos + 1]) == CELLTYPE_PBLACK || (cells[dypos - 1][dxpos + 1]) == CELLTYPE_WOMBLACK) {
				if (dypos - 2 <= 1) {
					CanFightOneMore(&canfightmoreCoords, dypos, dxpos, ct);
					for (const auto& coord : canfightmoreCoords) {
						int p = coord.first.first;
						int o = coord.first.second;
						fightCor->push_back(std::make_pair(std::make_pair(p, o), std::make_pair(p - 2, o + 2)));
					}
					return;
				}
				if ((cells[dypos - 2][dxpos + 2]) == CELLTYPE_EBLACK) {
					fightCor->push_back(std::make_pair(std::make_pair(dypos, dxpos), std::make_pair(dypos - 2, dxpos + 2)));
				}
			}
			if ((cells[dypos - 1][dxpos - 1]) == CELLTYPE_PBLACK || (cells[dypos - 1][dxpos - 1]) == CELLTYPE_WOMBLACK) {
				if (dypos - 2 <= 1) {
					CanFightOneMore(&canfightmoreCoords, dypos, dxpos, ct);
					for (const auto& coord : canfightmoreCoords) {
						int p = coord.first.first;
						int o = coord.first.second;
						fightCor->push_back(std::make_pair(std::make_pair(p, o), std::make_pair(p - 2, o - 2)));
					}
					return;
				}
				if ((cells[dypos - 2][dxpos - 2]) == CELLTYPE_EBLACK) {
					fightCor->push_back(std::make_pair(std::make_pair(dypos, dxpos), std::make_pair(dypos - 2, dxpos - 2)));
				}
			}
		}
		if (dypos + 2 >= boardsize) {
			return;
		}
		if ((cells[dypos + 1][dxpos + 1]) == CELLTYPE_PBLACK || (cells[dypos + 1][dxpos + 1]) == CELLTYPE_WOMBLACK) { //шашка
			if ((cells[dypos + 2][dxpos + 2]) == CELLTYPE_EBLACK) {
				if (cells[dypos][dxpos] == CELLTYPE_PWHITE || cells[dypos][dxpos] == CELLTYPE_WOMWHITE) {
					fightCor->push_back(std::make_pair(std::make_pair(dypos, dxpos), std::make_pair(dypos + 2, dxpos + 2)));
				}
			}
		}
		if ((cells[dypos + 1][dxpos - 1]) == CELLTYPE_PBLACK || (cells[dypos + 1][dxpos - 1]) == CELLTYPE_WOMBLACK) {
			if ((cells[dypos + 2][dxpos - 2]) == CELLTYPE_EBLACK) {
				if (cells[dypos][dxpos] == CELLTYPE_PWHITE || cells[dypos][dxpos] == CELLTYPE_WOMWHITE) {
					fightCor->push_back(std::make_pair(std::make_pair(dypos, dxpos), std::make_pair(dypos + 2, dxpos - 2)));
				}
			}
		}
		break;
	case CELLTYPE_PBLACK: //чёрные
		if ((cells[dypos][dxpos]) == CELLTYPE_WOMBLACK) { //Дамка
			if ((cells[dypos + 1][dxpos + 1]) == CELLTYPE_PWHITE || (cells[dypos + 1][dxpos + 1]) == CELLTYPE_WOMWHITE) {
				if (dypos + 2 >= boardsize) {
					CanFightOneMore(&canfightmoreCoords, dypos, dxpos, ct);
					for (const auto& coord : canfightmoreCoords) {
						int p = coord.first.first;
						int o = coord.first.second;
						fightCor->push_back(std::make_pair(std::make_pair(p, o), std::make_pair(p + 2, o + 2)));
					}
					return;
				}
				if ((cells[dypos + 2][dxpos + 2]) == CELLTYPE_EBLACK) {
					fightCor->push_back(std::make_pair(std::make_pair(dypos, dxpos), std::make_pair(dypos + 2, dxpos + 2)));

				}
			}
			if ((cells[dypos + 1][dxpos - 1]) == CELLTYPE_PWHITE || (cells[dypos + 1][dxpos - 1]) == CELLTYPE_WOMWHITE) {
				if (dypos + 2 >= boardsize) {
					CanFightOneMore(&canfightmoreCoords, dypos, dxpos, ct);
					for (const auto& coord : canfightmoreCoords) {
						int p = coord.first.first;
						int o = coord.first.second;
						fightCor->push_back(std::make_pair(std::make_pair(p, o), std::make_pair(p + 2, o - 2)));
					}
					return;
				}
				if ((cells[dypos + 2][dxpos - 2]) == CELLTYPE_EBLACK) {
					fightCor->push_back(std::make_pair(std::make_pair(dypos, dxpos), std::make_pair(dypos + 2, dxpos - 2)));

				}
			}
		}
		if (dypos - 2 <= 0) {
			return;
		}
		if ((cells[dypos - 1][dxpos + 1]) == CELLTYPE_PWHITE || (cells[dypos - 1][dxpos + 1]) == CELLTYPE_WOMWHITE) { //шашка
			if ((cells[dypos - 2][dxpos + 2]) == CELLTYPE_EBLACK) {
				if (cells[dypos][dxpos] == CELLTYPE_PBLACK || cells[dypos][dxpos] == CELLTYPE_WOMBLACK) {
					fightCor->push_back(std::make_pair(std::make_pair(dypos, dxpos), std::make_pair(dypos - 2, dxpos + 2)));
				}
			}
		}
		if ((cells[dypos - 1][dxpos - 1]) == CELLTYPE_PWHITE || (cells[dypos - 1][dxpos - 1]) == CELLTYPE_WOMWHITE) {
			if ((cells[dypos - 2][dxpos - 2]) == CELLTYPE_EBLACK) {
				if (cells[dypos][dxpos] == CELLTYPE_PBLACK || cells[dypos][dxpos] == CELLTYPE_WOMBLACK) {
					fightCor->push_back(std::make_pair(std::make_pair(dypos, dxpos), std::make_pair(dypos - 2, dxpos - 2)));
				}
			}
		}
		break;
	}
}

bool ChekersBoard::MovesRule(int xpos, int ypos, int dxpos, int dypos, CellType ct, CellType wct) { //правила хода
	
	if (cells[dypos][dxpos] != ct && cells[dypos][dxpos] != wct) {
		return false;
	}
	if (iisWoman(dxpos, dypos)) {
		if (std::abs(xpos - dxpos) != 1 || std::abs(ypos - dypos) != 1) {
			return false;
		}
		return true;
	}
	switch (ct)
	{
	case CELLTYPE_PWHITE:
		if (std::abs(xpos - dxpos) != 1 || ypos - dypos != 1) {
			return false;
		}
		return true;
		break;
	case CELLTYPE_PBLACK:
		if (std::abs(dxpos - xpos) != 1 || dypos - ypos != 1) {
			return false;
		}
		return true;
		break;
	}
}

bool ChekersBoard::Woman(int ypos, CellType ct) { //становление дамки
	for (int i = 1; i < boardsize; i++) {
		switch (ct)
		{
		case CELLTYPE_PWHITE:
			if (ypos == 8) {
				return true;
			}
			break;
		case CELLTYPE_PBLACK:
			if (ypos == 1) {
				return true;
			}
			break;
		}
	}
	return false;
}

bool ChekersBoard::iisWoman(int dxpos, int dypos) { //является ли пешка дамкой
	if (cells[dypos][dxpos] == CELLTYPE_WOMWHITE || cells[dypos][dxpos] == CELLTYPE_WOMBLACK) {
		return true;
	}
	return false;
}

void ChekersBoard::CanFightOneMore(std::vector<std::pair<std::pair<int, int>, bool>>* canfightonemoreCoordsint, int dypos, int dxpos, CellType ct) {
	if (ct == CELLTYPE_PWHITE) { //белые
		if (dypos + 2 >= boardsize) {
			return;
		}
		if ((cells[dypos + 1][dxpos + 1]) == CELLTYPE_PBLACK || (cells[dypos + 1][dxpos + 1]) == CELLTYPE_WOMBLACK) { //шашка
			if ((cells[dypos + 2][dxpos + 2]) == CELLTYPE_EBLACK) {
				if (cells[dypos][dxpos] == CELLTYPE_PWHITE || cells[dypos][dxpos] == CELLTYPE_WOMWHITE) {
					side = false;
					canfightonemoreCoordsint->push_back(std::make_pair(std::make_pair(dypos, dxpos), side));
				}
			}
		}
		if ((cells[dypos + 1][dxpos - 1]) == CELLTYPE_PBLACK || (cells[dypos + 1][dxpos - 1]) == CELLTYPE_WOMBLACK) {
			if ((cells[dypos + 2][dxpos - 2]) == CELLTYPE_EBLACK) {
				if (cells[dypos][dxpos] == CELLTYPE_PWHITE || cells[dypos][dxpos] == CELLTYPE_WOMWHITE) {
					side = true;
					canfightonemoreCoordsint->push_back(std::make_pair(std::make_pair(dypos, dxpos), side));
				}
			}
		}
	}
	if (ct == CELLTYPE_PBLACK) { //чёрные
		if (dypos - 2 <= 0) {
			return;
		}
		if ((cells[dypos - 1][dxpos + 1]) == CELLTYPE_PWHITE || (cells[dypos - 1][dxpos + 1]) == CELLTYPE_WOMWHITE) { //шашка
			if ((cells[dypos - 2][dxpos + 2]) == CELLTYPE_EBLACK) {
				if (cells[dypos][dxpos] == CELLTYPE_PBLACK || cells[dypos][dxpos] == CELLTYPE_WOMBLACK) {
					side = false;
					canfightonemoreCoordsint->push_back(std::make_pair(std::make_pair(dypos, dxpos), side));
				}
			}
		}
		if ((cells[dypos - 1][dxpos - 1]) == CELLTYPE_PWHITE || (cells[dypos - 1][dxpos - 1]) == CELLTYPE_WOMWHITE) {
			if ((cells[dypos - 2][dxpos - 2]) == CELLTYPE_EBLACK) {
				if (cells[dypos][dxpos] == CELLTYPE_PBLACK || cells[dypos][dxpos] == CELLTYPE_WOMBLACK) {
					side = true;
					canfightonemoreCoordsint->push_back(std::make_pair(std::make_pair(dypos, dxpos), side));
				}
			}
		}
	}
}

void ChekersBoard::CanFight(std::vector<std::pair<std::pair<int, int>, bool>>* canfightCoords, int dypos, int dxpos, CellType ct) {
	std::vector<std::pair<std::pair<int, int>, bool>> canfightmoreCoords;
	if (ct == CELLTYPE_PWHITE) { //белые
		if ((cells[dypos][dxpos]) == CELLTYPE_WOMWHITE) { //Дамка
			if ((cells[dypos - 1][dxpos + 1]) == CELLTYPE_PBLACK || (cells[dypos - 1][dxpos + 1]) == CELLTYPE_WOMBLACK) {
				if (dypos - 2 <= 0) {
					CanFightOneMore(&canfightmoreCoords, dypos, dxpos, ct);
					for (const auto& coord : canfightmoreCoords) {
						int p = coord.first.first;
						int o = coord.first.second;
						bool cside = coord.second;
						canfightCoords->push_back(std::make_pair(std::make_pair(p, o), cside));
					}
					return;
				}
				if ((cells[dypos - 2][dxpos + 2]) == CELLTYPE_EBLACK) {
					side = false;
					canfightCoords->push_back(std::make_pair(std::make_pair(dypos, dxpos), side));

				}
			}
			if ((cells[dypos - 1][dxpos - 1]) == CELLTYPE_PBLACK || (cells[dypos - 1][dxpos - 1]) == CELLTYPE_WOMBLACK) {
				if (dypos - 2 <= 0) {
					CanFightOneMore(&canfightmoreCoords, dypos, dxpos, ct);
					for (const auto& coord : canfightmoreCoords) {
						int p = coord.first.first;
						int o = coord.first.second;
						bool cside = coord.second;
						canfightCoords->push_back(std::make_pair(std::make_pair(p, o), cside));
					}
					return;
				}
				if ((cells[dypos - 2][dxpos - 2]) == CELLTYPE_EBLACK) {
					side = true;
					canfightCoords->push_back(std::make_pair(std::make_pair(dypos, dxpos), side));

				}
			}
		}
		if (dypos + 2 >= boardsize) {
			return;
		}
		if (dypos != 8) {
			if ((cells[dypos + 1][dxpos + 1]) == CELLTYPE_PBLACK || (cells[dypos + 1][dxpos + 1]) == CELLTYPE_WOMBLACK) { //шашка
				if ((cells[dypos + 2][dxpos + 2]) == CELLTYPE_EBLACK) {
					if (cells[dypos][dxpos] == CELLTYPE_PWHITE || cells[dypos][dxpos] == CELLTYPE_WOMWHITE) {
						side = false;
						canfightCoords->push_back(std::make_pair(std::make_pair(dypos, dxpos), side));
					}
				}
			}
			if ((cells[dypos + 1][dxpos - 1]) == CELLTYPE_PBLACK || (cells[dypos + 1][dxpos - 1]) == CELLTYPE_WOMBLACK) {
				if ((cells[dypos + 2][dxpos - 2]) == CELLTYPE_EBLACK) {
					if (cells[dypos][dxpos] == CELLTYPE_PWHITE || cells[dypos][dxpos] == CELLTYPE_WOMWHITE) {
						side = true;
						canfightCoords->push_back(std::make_pair(std::make_pair(dypos, dxpos), side));
					}
				}
			}
		}
	}
	if (ct == CELLTYPE_PBLACK) { //чёрные
		if ((cells[dypos][dxpos]) == CELLTYPE_WOMBLACK) { //Дамка
			if (dypos != 8) {
				if ((cells[dypos + 1][dxpos + 1]) == CELLTYPE_PWHITE || (cells[dypos + 1][dxpos + 1]) == CELLTYPE_WOMWHITE) {
					if (dypos + 2 >= boardsize) {
						CanFightOneMore(&canfightmoreCoords, dypos, dxpos, ct);
						for (const auto& coord : canfightmoreCoords) {
							int p = coord.first.first;
							int o = coord.first.second;
							bool cside = coord.second;
							canfightCoords->push_back(std::make_pair(std::make_pair(p, o), cside));
						}
						return;
					}
					if ((cells[dypos + 2][dxpos + 2]) == CELLTYPE_EBLACK) {

						side = false;
						canfightCoords->push_back(std::make_pair(std::make_pair(dypos, dxpos), side));

					}
				}
				if ((cells[dypos + 1][dxpos - 1]) == CELLTYPE_PWHITE || (cells[dypos + 1][dxpos - 1]) == CELLTYPE_WOMWHITE) {
					if (dypos + 2 >= boardsize) {
						CanFightOneMore(&canfightmoreCoords, dypos, dxpos, ct);
						for (const auto& coord : canfightmoreCoords) {
							int p = coord.first.first;
							int o = coord.first.second;
							bool cside = coord.second;
							canfightCoords->push_back(std::make_pair(std::make_pair(p, o), cside));
						}
						return;
					}
					if ((cells[dypos + 2][dxpos - 2]) == CELLTYPE_EBLACK) {

						side = true;
						canfightCoords->push_back(std::make_pair(std::make_pair(dypos, dxpos), side));

					}
				}
			}
		}
		if (dypos - 2 <= 0) {
			return;
		}
		if ((cells[dypos - 1][dxpos + 1]) == CELLTYPE_PWHITE || (cells[dypos - 1][dxpos + 1]) == CELLTYPE_WOMWHITE) { //шашка
			if ((cells[dypos - 2][dxpos + 2]) == CELLTYPE_EBLACK) {
				if (cells[dypos][dxpos] == CELLTYPE_PBLACK || cells[dypos][dxpos] == CELLTYPE_WOMBLACK) {
					side = false;
					canfightCoords->push_back(std::make_pair(std::make_pair(dypos, dxpos), side));
				}
			}
		}
		if ((cells[dypos - 1][dxpos - 1]) == CELLTYPE_PWHITE || (cells[dypos - 1][dxpos - 1]) == CELLTYPE_WOMWHITE) {
			if ((cells[dypos - 2][dxpos - 2]) == CELLTYPE_EBLACK) {
				if (cells[dypos][dxpos] == CELLTYPE_PBLACK || cells[dypos][dxpos] == CELLTYPE_WOMBLACK) {
					side = true;
					canfightCoords->push_back(std::make_pair(std::make_pair(dypos, dxpos), side));
				}
			}
		}
	}
}

bool ChekersBoard::OneMore(int xpos, int ypos, int dxpos, int dypos, CellType ct) { // повторное нападение
	std::vector<std::pair<std::pair<int, int>, bool>> FightCoords;
	CanFight(&FightCoords, ypos, xpos, ct);
	return !FightCoords.empty();
}

bool ChekersBoard::onlyFightRule(int xpos, int ypos, int dxpos, int dypos, CellType ct) {
	std::vector<std::pair<std::pair<int, int>, bool>> coords;
	onlyFightcheck(ct, &coords);
	int count = 0;
	int total = coords.size();
	for (const auto& coord : coords) {
		count++;
		int j = coord.first.first;
		int i = coord.first.second;
		bool sside = coord.second;
		if (i != dxpos || j != dypos) {
			if (count == total)
				return false;
			else
				continue;
		}
		switch (ct)
		{
		case CELLTYPE_PWHITE:
			switch (sside)
			{
			case true:
				if (cells[dypos][dxpos] == CELLTYPE_WOMWHITE) {
					if (std::abs(ypos - j) == 2 && std::abs(xpos - i) == 2 && (cells[ypos + 1][xpos + 1] == CELLTYPE_PBLACK || cells[ypos + 1][xpos + 1] == CELLTYPE_WOMBLACK)) {
						cells[ypos + 1][xpos + 1] = CELLTYPE_EBLACK;
						return true;
					}
				}
				if (ypos - j != 2 || std::abs(xpos - i) != 2 || (cells[ypos - 1][xpos + 1] != CELLTYPE_PBLACK && cells[ypos - 1][xpos + 1] != CELLTYPE_WOMBLACK)) {
					if (count == total)
						return false;
					else
						continue;
				}
				else {
					cells[ypos - 1][xpos + 1] = CELLTYPE_EBLACK;
					return true;
				}
				break;
			case false:
				if (cells[dypos][dxpos] == CELLTYPE_WOMWHITE) {
					if (std::abs(ypos - j) == 2 && std::abs(xpos - i) == 2 && (cells[ypos + 1][xpos - 1] == CELLTYPE_PBLACK || cells[ypos + 1][xpos - 1] == CELLTYPE_WOMBLACK)) {
						cells[ypos + 1][xpos - 1] = CELLTYPE_EBLACK;
						return true;
					}
				}
				if (ypos - j != 2 || std::abs(xpos - i) != 2 || (cells[ypos - 1][xpos - 1] != CELLTYPE_PBLACK && cells[ypos - 1][xpos - 1] != CELLTYPE_WOMBLACK)) {
					if (count == total) {
						return false;
					}
					else
						continue;
				}
				else {
					cells[ypos - 1][xpos - 1] = CELLTYPE_EBLACK;
					return true;
				}
				break;
			}
			break;
		case CELLTYPE_PBLACK:
			switch (sside)
			{
			case true:
				if (cells[dypos][dxpos] == CELLTYPE_WOMBLACK) {
					if (std::abs(j - ypos) == 2 && std::abs(xpos - i) == 2 && (cells[ypos - 1][xpos + 1] == CELLTYPE_PWHITE || cells[ypos - 1][xpos + 1] == CELLTYPE_WOMWHITE)) {
						cells[ypos - 1][xpos + 1] = CELLTYPE_EBLACK;
						return true;
					}
				}
				if (j - ypos != 2 || std::abs(xpos - i) != 2 || (cells[ypos + 1][xpos + 1] != CELLTYPE_PWHITE && cells[ypos + 1][xpos + 1] != CELLTYPE_WOMWHITE)) {
					if (count == total)
						return false;
					else
						continue;
				}
				else {
					cells[ypos + 1][xpos + 1] = CELLTYPE_EBLACK;
					return true;
				}
				break;
			case false:
				if (cells[dypos][dxpos] == CELLTYPE_WOMBLACK) {
					if (std::abs(j - ypos) == 2 && std::abs(xpos - i) == 2 && (cells[ypos - 1][xpos - 1] == CELLTYPE_PWHITE || cells[ypos - 1][xpos - 1] == CELLTYPE_WOMWHITE)) {
						cells[ypos - 1][xpos - 1] = CELLTYPE_EBLACK;
						return true;
					}
				}
				if (j - ypos != 2 || std::abs(xpos - i) != 2 || (cells[ypos + 1][xpos - 1] != CELLTYPE_PWHITE && cells[ypos + 1][xpos - 1] != CELLTYPE_WOMWHITE)) {
					if (count == total)
						return false;
					else
						continue;
				}
				else {
					cells[ypos + 1][xpos - 1] = CELLTYPE_EBLACK;
					return true;
				}
				break;
			}
			break;
		}
	}
}

bool ChekersBoard::onlyFight(CellType ct) {
	std::vector<std::pair<std::pair<int, int>, bool>> coords;
	onlyFightcheck(ct, &coords);
	for (const auto& coord : coords) {
		int j = coord.first.first;
		int i = coord.first.second;
		bool sside = coord.second;
	}
	return !coords.empty();
}

void ChekersBoard::onlyFightcheck(CellType ct, std::vector<std::pair<std::pair<int, int>, bool>>* validCoords) {
	std::vector<std::pair<std::pair<int, int>, bool>> fightCoords;
	for (int i = 1; i < boardsize; i++) {
		for (int j = 0; j < boardsize; j++) {
			CanFight(&fightCoords, j, i, ct);
			for (const auto& coord : fightCoords) {
				int p = coord.first.first;
				int o = coord.first.second;
				bool cside = coord.second;
				validCoords->push_back(std::make_pair(std::make_pair(p, o), cside));
			}
		}
	}
}

bool ChekersBoard::CheckEndConditionScorecounter() { //победа
	int blackcount = 0;
	int whitecount = 0;
	

	for (int i = 1; i < boardsize; i++) {
		for (int j = 0; j < boardsize; j++) {
			if (cells[i][j] == CELLTYPE_PBLACK || cells[i][j] == CELLTYPE_WOMBLACK)
				blackcount++;
			if (cells[i][j] == CELLTYPE_PWHITE || cells[i][j] == CELLTYPE_WOMWHITE)
				whitecount++;
		}
	}
	if ((whitecount > 0) && (blackcount > 0)) {
		if (whitecount > 9 && blackcount > 9)
			std::cout << "           " << "\033[37;42m" << whitecount << "/12\033[0m" << " -- " << "\033[31;42m" << blackcount << "/12\033[0m" << std::endl;
		else
			std::cout << "            " << "\033[37;42m" << whitecount << "/12\033[0m" << " -- " << "\033[31;42m" << blackcount << "/12\033[0m" << std::endl;
	}
	if (blackcount < 1 || whitecount < 1)
		return true;

	if (sC.empty() && fC.empty()) {

		return true;
	}
	return false;	
}