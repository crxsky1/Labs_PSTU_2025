#include <iostream>
#include <vector>

using namespace std;


class Bankomat {
private:
	int currentBankomatId; // Идентификационный номер
	double quantyMoneyInBankomat; // Колво денег в банкомате
	double maximumWithdrawalAmount; // Максимальная сумма для снятия 
	// (можно снять только 10 процентов от суммы в банкомате)

public:
	Bankomat() {
		currentBankomatId = rand();
		quantyMoneyInBankomat = 999999;
		maximumWithdrawalAmount = quantyMoneyInBankomat / 10;
	}
	Bankomat(int bid, double qmib) {
		currentBankomatId = bid;
		quantyMoneyInBankomat = qmib;
		maximumWithdrawalAmount = qmib / 10;
	}
	Bankomat(const Bankomat& b) {
		currentBankomatId = rand();
		quantyMoneyInBankomat = b.quantyMoneyInBankomat;
		maximumWithdrawalAmount = b.quantyMoneyInBankomat / 10;
	}

	int getId() const { return currentBankomatId; }
	double getQuantyMoneyInBankomat() const { return quantyMoneyInBankomat; }
	double getMaximumWithdrawalAmount() const { return maximumWithdrawalAmount; }

	void withdrawMoney(double  withdrawalAmount) {
		if (withdrawalAmount <= maximumWithdrawalAmount) {
			quantyMoneyInBankomat -= withdrawalAmount;
			maximumWithdrawalAmount = quantyMoneyInBankomat / 10;
		}
		else cout << " невозможно столько снять, операция отклонена" << endl;
	}
	void depositMoney(double deposit) {
		quantyMoneyInBankomat += deposit;
		maximumWithdrawalAmount = quantyMoneyInBankomat / 10;

	}

	~Bankomat() {

	}
};


int main() {
	srand(time(0));
	setlocale(LC_ALL, "ru");

	vector<Bankomat*> bankomats;

	Bankomat* bankomat0 = new Bankomat();
	Bankomat* bankomat1 = new Bankomat(1380, 500000);
	Bankomat* bankomat2 = new Bankomat();

	bankomats.push_back(bankomat0);
	bankomats.push_back(bankomat1);
	bankomats.push_back(bankomat2);


	int i = 0;
	int cond = -1;
	int bid;
	int qm;

	while (cond != 0 && bankomats.size() > 0) {
		i = 0;
		cout << " | номер банкомата | " << "айди банкомата |" << " сумма которая есть в банкомате |" << " максимальная сумма для снятия |" << endl;
		for (auto bankomat : bankomats) {
			cout << "   " << i << " \t\t   | " << bankomat->getId() << "\t    | " << bankomat->getQuantyMoneyInBankomat() << "\t\t\t     | " << bankomat->getMaximumWithdrawalAmount() << "\t\t\t     |" << endl;
			i++;
		}

		cout << endl;
		cout << " действия: " << endl;
		cout << "  0. закончить" << endl;
		cout << "  1. снять сумму с банкомата" << endl;
		cout << "  2. положить деньг на счет" << endl;
		cout << "  3. создать новый банкомат" << endl;
		cout << "  4. удалить существующий банкомат" << endl;


		cout << " ";
		cin >> cond;
		switch (cond) {
		case 1:
			cout << " Введите номер банкомата: ";
			cin >> bid;
			if (bid > bankomats.size()) {
				cout << " Неверный номер банкомата";
				break;
			}
			cout << " Введите количесво денег для снятия (до " << bankomats[bid]->getMaximumWithdrawalAmount() << "): ";
			cin >> qm;
			bankomats[bid]->withdrawMoney(qm);

			break;
		case 2:
			cout << " Введите номер банкомата: ";
			cin >> bid;
			if (bid > bankomats.size()) {
				cout << " Неверный номер банкомата";
				break;
			}
			cout << " Введите сколько денег хотите положить: ";
			cin >> qm;
			bankomats[bid]->depositMoney(qm);
			break;

		case 3:
			cout << " Введите id банкомата (0 - случайный номер): ";
			cin >> bid;
			cout << " Введите сколько будет в банкомате денег: ";
			cin >> qm;

			bankomats.push_back(new Bankomat((bid == 0) ? rand() : bid, qm));

			break;

		case 4:
			cout << " Введите id банкомата: ";
			cin >> bid;

			delete bankomats[bid];
			bankomats.erase(bankomats.cbegin() + bid);

			break;

		default:
			break;
		}
		cout << endl << endl << endl;

	}


	for (auto bankomat : bankomats) {
		delete bankomat;
	}
	bankomats.clear();
}
