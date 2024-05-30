#include "BotPlayer.h"

bool BotPlayer::MakeMove(int bufdcol, int bufdrow) {
	std::cout << "\033[32m====================================\033[0m" << std::endl;
	std::cout << "����� " << "\033[42m" << name << "\033[0m" << ", ��� ���..." << std::endl;
	std::cout << "����� ������� ������?" << std::endl;
	std::cout << "������� ����������(A1-B2): ";


	std::vector<MonteCarlo*> evaluators;
	if (this->board->onlyFight(this->cellType)) {
		std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> Fightcor;
		this->board->FightStep(this->cellType, &Fightcor);
		for (const auto& coord : Fightcor) {
			mdrow = coord.first.first;
			mdcol = coord.first.second;
			mrow = coord.second.first;
			mcol = coord.second.second;
			evaluators.push_back(new MonteCarlo(this->board, 100, (this->cellType == CELLTYPE_PWHITE) ? CELLTYPE_PBLACK : CELLTYPE_PWHITE, mdrow, mdcol, mrow, mcol));
		}
	}
	else {
		std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> Simplcor;
		this->board->SimpleStep(this->cellType, &Simplcor);
		for (const auto& coord : Simplcor) {
			mdrow = coord.first.first;
			mdcol = coord.first.second;
			mrow = coord.second.first;
			mcol = coord.second.second;
			evaluators.push_back(new MonteCarlo(this->board, 100, (this->cellType == CELLTYPE_PWHITE) ? CELLTYPE_PBLACK : CELLTYPE_PWHITE, mdrow, mdcol, mrow, mcol));
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
	
	mdcol = biggestWinEvaluaters[0]->dGetYpos();
	mdrow = biggestWinEvaluaters[0]->dGetXpos();
	mcol = biggestWinEvaluaters[0]->GetYpos();
	mrow = biggestWinEvaluaters[0]->GetXpos();

	dletter = mdrow + '@';
	letter = mrow + '@';

	std::cout << dletter << mdcol << letter << mcol << std::endl;
	std::cout << "\033[32m====================================\033[0m" << std::endl;

	//������ �����
	if (onlyfightcount != onmorecount) {
		if (this->board->CheckLegal(mcol, mrow, bufdcol, bufdrow, mdcol, mdrow, this->cellType)) {
			if (this->board->onlyFightRule(mcol, mrow, mdcol, mdrow, this->cellType)) {
				if (this->board->Woman(mrow, this->cellType)) {
					this->board->SetCell(mcol, mrow, this->wcellType, mdcol, mdrow, this->dcellType);
				}
				else if (this->board->iisWoman(mdcol, mdrow)) {
					this->board->SetCell(mcol, mrow, this->wcellType, mdcol, mdrow, this->dcellType); //��������� ���� �����
				}
				else {
					this->board->SetCell(this->cellType, mcol, mrow, mdcol, mdrow, this->dcellType);
				}
				if (this->board->OneMore(mcol, mrow, mdcol, mdrow, this->cellType)) {
					board->Show();
					return MakeMove(mcol, mrow);
				}
				else
				{
					onlyfightcount++;
					for (auto evaluator = evaluators.begin(); evaluator != evaluators.end(); evaluator++)
						delete (*evaluator);
					evaluators.clear();
					biggestWinEvaluaters.clear();
					return true;
				}
			}
			else {
				std::cout << "       \033[37;42m�� ������� ������ �����\033[0m" << std::endl;
				board->Show();
				return MakeMove(bufdcol, bufdrow);
			}
		}
		else {
			std::cout << "       \033[37;42m�� ������� ������ �����\033[0m" << std::endl;
			board->Show();
			return MakeMove(bufdcol, bufdrow);
		}
	}
	//������ ����
	if (this->board->onlyFight(this->cellType)) { // ���� ����
		if (this->board->onlyFightRule(mcol, mrow, mdcol, mdrow, this->cellType)) { //���� ���������� ��� �����
			if (this->board->Woman(mrow, this->cellType)) { //����������� ����� [8]
				this->board->SetCell(mcol, mrow, this->wcellType, mdcol, mdrow, this->dcellType); //��������� ���� �����
			}
			else if (this->board->iisWoman(mdcol, mdrow)) {
				this->board->SetCell(mcol, mrow, this->wcellType, mdcol, mdrow, this->dcellType); //��������� ���� �����
			}
			else {
				this->board->SetCell(this->cellType, mcol, mrow, mdcol, mdrow, this->dcellType); //��������� ���� �����
			}
			if (this->board->OneMore(mcol, mrow, mdcol, mdrow, this->cellType)) { // ���� ��� ����
				board->Show();
				onmorecount++;
				return MakeMove(mcol, mrow);
			}
			else
			{
				for (auto evaluator = evaluators.begin(); evaluator != evaluators.end(); evaluator++)
					delete (*evaluator);
				evaluators.clear();
				biggestWinEvaluaters.clear();
				return true; //���� �������� - ����� ����
			}
		}
		else {
			std::cout << "       \033[37;42m�� ������� ������ �����\033[0m" << std::endl;
			for (auto evaluator = evaluators.begin(); evaluator != evaluators.end(); evaluator++)
				delete (*evaluator);
			evaluators.clear();
			biggestWinEvaluaters.clear();
			return false; // ���� ����, �� ����� �� ���
		}
	}
	//������� ����
	if (this->board->CheckLegal(mcol, mrow, mdcol, mdrow, this->cellType, this->wcellType)) { //������� �������� ���� �����
		if (this->board->Woman(mrow, this->cellType)) { //����������� �����
			this->board->SetCell(mcol, mrow, this->wcellType, mdcol, mdrow, this->dcellType); //��������� ���� �����
		}
		else if (this->board->iisWoman(mdcol, mdrow)) { //�������� �� ����� ������
			this->board->SetCell(mcol, mrow, this->wcellType, mdcol, mdrow, this->dcellType); //��������� ���� �����
		}
		else {
			this->board->SetCell(this->cellType, mcol, mrow, mdcol, mdrow, this->dcellType); //��������� ���� �����
		}
		for (auto evaluator = evaluators.begin(); evaluator != evaluators.end(); evaluator++)
			delete (*evaluator);
		evaluators.clear();
		biggestWinEvaluaters.clear();
		return true;
	}
	for (auto evaluator = evaluators.begin(); evaluator != evaluators.end(); evaluator++)
		delete (*evaluator);
	evaluators.clear();
	biggestWinEvaluaters.clear();
	return false;
}