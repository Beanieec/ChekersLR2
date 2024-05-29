#include "GameManager.h"
#include "HumPlayer.h"
#include "BotPlayer.h"
#include "RandPlayer.h"

GameManager::GameManager() {}

bool GameManager::Init() {
	int boardsize = 9;
	std::string playerType;
	std::string playerName;
	this->board = new ChekersBoard(boardsize);

	std::cout << "������� ��� \033[31;47m1-��\033[0m ������(HUM/PC): ";
	std::getline(std::cin, playerType);
	if (playerType == "HUM")
		this->player1 = new HumPlayer();
	else if (playerType == "PC")
		this->player1 = new BotPlayer();
	else
		this->player1 = new BotPlayer();

	std::cout << "������� ��� \033[41m2-��\033[0m ������(HUM/PC): ";
	std::getline(std::cin, playerType);
	if (playerType == "HUM")
		this->player2 = new HumPlayer();
	else if (playerType == "PC")
		this->player2 = new BotPlayer();
	else
		this->player2 = new RandPlayer();
	
	std::cout << "������� ��� ������, ��������� \033[47m \033[0m: ";
	std::getline(std::cin, playerName);
	player1->SetupPlayer(playerName, CELLTYPE_PWHITE, CELLTYPE_EBLACK, CELLTYPE_WOMWHITE);
	std::cout << "������� ��� ������, ��������� \033[41m \033[0m: ";
	std::getline(std::cin, playerName);
	std::cout << std::endl;

	player2->SetupPlayer(playerName, CELLTYPE_PBLACK, CELLTYPE_EBLACK, CELLTYPE_WOMBLACK);
	player2->SetBoard(this->board);
	player1->SetBoard(this->board);
	currentPlayer = player1;
	std::cout << "������� ����� ����� ��� - " << wh << " ; " << bk << std::endl;
	std::cout << "����� ����� ��� - " << kwh << " ; " << kbk << std::endl;
	std::cout << "\033[32m====================================\033[0m" << std::endl;

	return true;
}

GameManager::~GameManager() {
	delete this->player2;
	delete this->player1;
	delete this->board;
}

void GameManager::ShowBoard() {
	this->board->Show();
}

void GameManager::MakeMove() {
	ShowBoard();
	while (!currentPlayer->MakeMove(0, 0)) {
		std::cout << "  \033[4;41m������������ ���, ���������� ���\033[0m" << std::endl;
		ShowBoard();
	}
	if (this->board->CheckEndConditionScorecounter()) {
		if (this->board->CheckEndConditionScorecounter())
			std::cout << "          \033[4;42m" << "����� " << currentPlayer->GetName() << " �������!" << "\033[0m" << std::endl;
		else
			std::cout << "�����!" << std::endl;
		this->bGameFinished = true;
		ShowBoard();
		std::cout << "              \033[41m�����...\033[0m" << std::endl;
		std::cout << "\033[32m====================================\033[0m" << std::endl;
		return;
	}
	currentPlayer = (currentPlayer == player1) ? player2 : player1;
}

bool GameManager::IsGameFinished() {
	return bGameFinished;
}