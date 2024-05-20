#include <iostream>
#include <Windows.h>
#include "ChekersBoard.h"
#include "GameManager.h"
#include "HumPlayer.h"
#include "CellType.h"

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	GameManager manager;
	if (!manager.Init()) {
		std::cout << "Неверные данные, выходим...";
		return 0;
	}
	while (!manager.IsGameFinished()) {
		manager.MakeMove();
	}
	
	SetConsoleCP(866);
	system("pause");
	return 228;
}