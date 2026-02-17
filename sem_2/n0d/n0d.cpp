#include <iostream>
using namespace std;

int nod(int n, int m) {
	if (n == m) return n;
	if (n > m) return nod(n - m, m);
	return nod(n, m - n);
}

int main() {
	cout << " nod(10, 3)" << "\t" << nod(10, 3) << endl;
	cout << " nod(40, 12)" << "\t" << nod(40, 12) << endl;
	cout << " nod(13, 13)" << "\t" << nod(13, 13) << endl;
	cout << " nod(5, 25)" << "\t" << nod(5, 25) << endl;
}