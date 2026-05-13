#include <iostream>
#include <string>

using namespace std;

class Pair
{
public:
	int first;
	double second;

	Pair(int f, double s) {
		first = f;
		second = s;
	}
	~Pair() {

	}

	friend ostream& operator<<(ostream& out, const Pair& pair) {
		out << pair.first << ":" << pair.second;
		return out;
	}


};
#include "list.h"

int main() {
	List<int> listI = { 1, 2, 3, 4 };
	List<double> listD = { 1.1, 2.2, 3.3, 4.4 };
	List<string> listS = { "1s", "2s", "3s", "4s" };
	List<Pair> listP = { { 1, 0.1 }, { 2, 0.2 }, { 3, 0.3}, { 4, 0.4 } };


	for (auto it = listI.begin(); it != listI.end(); it++) {
		cout << *it << "\t";
	}
	cout << endl;
	for (auto it = listD.begin(); it != listD.end(); it++) {
		cout << *it << "\t";
	}
	cout << endl;
	for (auto it = listS.begin(); it != listS.end(); it++) {
		cout << *it << "\t";
	}
	cout << endl;
	for (auto it = listP.begin(); it != listP.end(); it++) {
		cout << *it << "\t";
	}
	cout << endl;

}
