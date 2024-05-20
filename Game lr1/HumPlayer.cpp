#include "HumPlayer.h"

HumPlayer::HumPlayer() {}

HumPlayer::~HumPlayer() {}

void HumPlayer::SetupPlayer(std::string name, CellType cellType, CellType dcellType, CellType wcellType) {
	this->name = name;
	this->cellType = cellType;
	this->dcellType = dcellType;
	this->wcellType = wcellType;
}

void HumPlayer::SetBoard(ChekersBoard* board) {
	this->board = board;
}

bool HumPlayer::MakeMove(int bufdcol, int bufdrow) {
	std::cout << "\033[32m====================================\033[0m" << std::endl;
	std::cout << "»грок " << "\033[42m" << name << "\033[0m" << ", ваш ход..." << std::endl;
	std::cout << " акой фигурой пойдЄте?" << std::endl;
	std::cout << "¬ведите координаты(A1-B2): ";
	std::cin >> dletter >> dcol >> letter >> col;
	std::cout << "\033[32m====================================\033[0m" << std::endl;

	drow = dletter - '@';
	row = letter - '@';
	
	//повтор удара
	if (onlyfightcount != onmorecount) {
		if (this->board->CheckLegal(col, row, bufdcol, bufdrow, dcol, drow, this->cellType)) {
			if (this->board->onlyFightRule(col, row, dcol, drow, this->cellType)) {
				if (this->board->Woman(row, this->cellType)) {
					this->board->SetCell(col, row, this->wcellType, dcol, drow, this->dcellType);
				}
				else if (this->board->iisWoman(dcol, drow)) {
					this->board->SetCell(col, row, this->wcellType, dcol, drow, this->dcellType); //отрисовка хода дамки
				}
				else {
					this->board->SetCell(this->cellType, col, row, dcol, drow, this->dcellType);
				}
				if (this->board->OneMore(col, row, dcol, drow, this->cellType)) {
					board->Show();
					return MakeMove(col, row);
				}
				else
				{
					onlyfightcount++;
					return true;
				}
			}
			else {
				std::cout << "       \033[37;42m¬џ ќЅя«јЌџ ƒќЅ»“№ ЎјЎ ”\033[0m" << std::endl;
				board->Show();
				return MakeMove(bufdcol, bufdrow);
			}
		}
		else {
			std::cout << "       \033[37;42m¬џ ќЅя«јЌџ ƒќЅ»“№ ЎјЎ ”\033[0m" << std::endl;
			board->Show();
			return MakeMove(bufdcol, bufdrow);
		}
	}
	//первый удар
	if (this->board->onlyFight(this->cellType)) { // есть удар
		if (this->board->onlyFightRule(col, row, dcol, drow, this->cellType)) { //удар правильный дл€ шашки
			if (this->board->Woman(row, this->cellType)) { //становление дамки [8]
				this->board->SetCell(col, row, this->wcellType, dcol, drow, this->dcellType); //отрисовка хода дамки
			}
			else if (this->board->iisWoman(dcol, drow)) {
				this->board->SetCell(col, row, this->wcellType, dcol, drow, this->dcellType); //отрисовка хода дамки
			}
			else {
				this->board->SetCell(this->cellType, col, row, dcol, drow, this->dcellType); //отрисовка хода шашки
			}
			if (this->board->OneMore(col, row, dcol, drow, this->cellType)) { // есть ещЄ удар
				board->Show();
				onmorecount++;
				return MakeMove(col, row);
			}
			else
			{
				return true; //удар совершЄн - конец хода
			}
		}
		else {
			std::cout << "       \033[37;42m¬џ ќЅя«јЌџ —Џ≈—“№ ЎјЎ ”\033[0m" << std::endl;
			return false; // удар есть, но бьЄшь не так
		}
	}
	//простые ходы
	if (this->board->CheckLegal(col, row, dcol, drow, this->cellType, this->wcellType)) { //правила простого хода шашки
		if (this->board->Woman(row, this->cellType)) { //становление дамки
			this->board->SetCell(col, row, this->wcellType, dcol, drow, this->dcellType); //отрисовка хода дамки
		}
		else if (this->board->iisWoman(dcol, drow)) { //€вл€етс€ ли пешка дамкой
			this->board->SetCell(col, row, this->wcellType, dcol, drow, this->dcellType); //отрисовка хода дамки
		}
		else {
			this->board->SetCell(this->cellType, col, row, dcol, drow, this->dcellType); //отрисовка хода шашки
		}
		return true;
	}
	return false;
}

std::string HumPlayer::GetName() {
	return this->name;
}