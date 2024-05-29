#include "BotPlayer.h"

bool BotPlayer::MakeMove(int bufdcol, int bufdrow) {
	/*std::cout << "\033[32m====================================\033[0m" << std::endl;
	std::cout << "����� " << "\033[42m" << name << "\033[0m" << ", ��� ���..." << std::endl;
	std::cout << "����� ������� ������?" << std::endl;
	std::cout << "������� ����������(A1-B2): ";
	std::cin >> dletter >> dcol >> letter >> col;
	std::cout << "\033[32m====================================\033[0m" << std::endl;*/

	std::vector<MonteCarlo*> evaluators;
	if (this->board->onlyFight(this->cellType)) {
		std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> Fightcor;
		this->board->FightStep(this->cellType, &Fightcor);
		for (const auto& coord : Fightcor) {
			drow = coord.first.first;
			dcol = coord.first.second;
			row = coord.second.first;
			col = coord.second.second;
			evaluators.push_back(new MonteCarlo(this->board, 1000, (this->cellType == CELLTYPE_PWHITE) ? CELLTYPE_PBLACK : CELLTYPE_PWHITE, drow, dcol, row, col));
		}
	}
	else {
		std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> Simplcor;
		this->board->SimpleStep(this->cellType, &Simplcor);
		for (const auto& coord : Simplcor) {
			drow = coord.first.first;
			dcol = coord.first.second;
			row = coord.second.first;
			col = coord.second.second;
			evaluators.push_back(new MonteCarlo(this->board, 1000, (this->cellType == CELLTYPE_PWHITE) ? CELLTYPE_PBLACK : CELLTYPE_PWHITE, drow, dcol, row, col));
		}	
	}

	for (int i = 0; i < evaluators.size(); i++) {
		evaluators[i]->Evaluted();
	}

	int biggestVic = -1;

	for (auto evaluator = evaluators.begin(); evaluator != evaluators.end(); evaluator++)
		if (this->cellType == CELLTYPE_PWHITE) {
			if ((*evaluator)->GetVictor() > biggestVic)
				biggestVic = (*evaluator)->GetVictor();
		}
		else
		{
			if ((*evaluator)->GetVictor() > biggestVic)
				biggestVic = (*evaluator)->GetLose();
		}

	std::vector<MonteCarlo*> biggestWinEvaluaters;
	for (auto evaluator = evaluators.begin(); evaluator != evaluators.end(); evaluator++) {
		int numVictories;
		if (this->cellType == CELLTYPE_PWHITE)
			numVictories = (*evaluator)->GetVictor();
		else
			numVictories = (*evaluator)->GetLose();
		if (numVictories == biggestVic)
			biggestWinEvaluaters.push_back((*evaluator));
	}
	std::cout << "faa" << biggestWinEvaluaters[0]->dGetXpos() << biggestWinEvaluaters[0]->dGetYpos() << biggestWinEvaluaters[0]->GetXpos() << biggestWinEvaluaters[0]->GetYpos() << std::endl;
	this->board->SetCell(this->cellType, biggestWinEvaluaters[0]->GetYpos(), biggestWinEvaluaters[0]->GetXpos(),  biggestWinEvaluaters[0]->dGetYpos(), biggestWinEvaluaters[0]->dGetXpos(), this->dcellType);
	for (auto evaluator = evaluators.begin(); evaluator != evaluators.end(); evaluator++)
		delete (*evaluator);
	evaluators.clear();
	biggestWinEvaluaters.clear();
	return true;


	//drow = dletter - '@';
	//row = letter - '@';

	//std::cout << dletter << dcol << letter << col << std::endl;
	//std::cout << "\033[32m====================================\033[0m" << std::endl;

	////������ �����
	//if (onlyfightcount != onmorecount) {
	//	if (this->board->CheckLegal(col, row, bufdcol, bufdrow, dcol, drow, this->cellType)) {
	//		if (this->board->onlyFightRule(col, row, dcol, drow, this->cellType)) {
	//			if (this->board->Woman(row, this->cellType)) {
	//				this->board->SetCell(col, row, this->wcellType, dcol, drow, this->dcellType);
	//			}
	//			else if (this->board->iisWoman(dcol, drow)) {
	//				this->board->SetCell(col, row, this->wcellType, dcol, drow, this->dcellType); //��������� ���� �����
	//			}
	//			else {
	//				this->board->SetCell(this->cellType, col, row, dcol, drow, this->dcellType);
	//			}
	//			if (this->board->OneMore(col, row, dcol, drow, this->cellType)) {
	//				board->Show();
	//				return MakeMove(col, row);
	//			}
	//			else
	//			{
	//				onlyfightcount++;
	//				return true;
	//			}
	//		}
	//		else {
	//			std::cout << "       \033[37;42m�� ������� ������ �����\033[0m" << std::endl;
	//			board->Show();
	//			return MakeMove(bufdcol, bufdrow);
	//		}
	//	}
	//	else {
	//		std::cout << "       \033[37;42m�� ������� ������ �����\033[0m" << std::endl;
	//		board->Show();
	//		return MakeMove(bufdcol, bufdrow);
	//	}
	//}
	////������ ����
	//if (this->board->onlyFight(this->cellType)) { // ���� ����
	//	if (this->board->onlyFightRule(col, row, dcol, drow, this->cellType)) { //���� ���������� ��� �����
	//		if (this->board->Woman(row, this->cellType)) { //����������� ����� [8]
	//			this->board->SetCell(col, row, this->wcellType, dcol, drow, this->dcellType); //��������� ���� �����
	//		}
	//		else if (this->board->iisWoman(dcol, drow)) {
	//			this->board->SetCell(col, row, this->wcellType, dcol, drow, this->dcellType); //��������� ���� �����
	//		}
	//		else {
	//			this->board->SetCell(this->cellType, col, row, dcol, drow, this->dcellType); //��������� ���� �����
	//		}
	//		if (this->board->OneMore(col, row, dcol, drow, this->cellType)) { // ���� ��� ����
	//			board->Show();
	//			onmorecount++;
	//			return MakeMove(col, row);
	//		}
	//		else
	//		{
	//			return true; //���� �������� - ����� ����
	//		}
	//	}
	//	else {
	//		std::cout << "       \033[37;42m�� ������� ������ �����\033[0m" << std::endl;
	//		return false; // ���� ����, �� ����� �� ���
	//	}
	//}
	////������� ����
	//if (this->board->CheckLegal(col, row, dcol, drow, this->cellType, this->wcellType)) { //������� �������� ���� �����
	//	if (this->board->Woman(row, this->cellType)) { //����������� �����
	//		this->board->SetCell(col, row, this->wcellType, dcol, drow, this->dcellType); //��������� ���� �����
	//	}
	//	else if (this->board->iisWoman(dcol, drow)) { //�������� �� ����� ������
	//		this->board->SetCell(col, row, this->wcellType, dcol, drow, this->dcellType); //��������� ���� �����
	//	}
	//	else {
	//		this->board->SetCell(this->cellType, col, row, dcol, drow, this->dcellType); //��������� ���� �����
	//	}
	//	return true;
	//}
	//return false;
}