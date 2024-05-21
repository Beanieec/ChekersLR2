#include "Player.h"

void Player::SetupPlayer(std::string name, CellType cellType, CellType dcellType, CellType wcellType) {
	this->name = name;
	this->cellType = cellType;
	this->dcellType = dcellType;
	this->wcellType = wcellType;
}

void Player::SetBoard(ChekersBoard* board) {
	this->board = board;
}

std::string Player::GetName() {
	return this->name;
}