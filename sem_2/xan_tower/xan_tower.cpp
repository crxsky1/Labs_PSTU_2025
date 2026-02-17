
#include <iostream>
using namespace std;

// n - количество колец
// start - столбец начала
// point - цель куда кладем
// temp - вспомогательный столб
void xanoi(int n, int start, int point, int temp) {
	if (n <= 0) return;
	xanoi(n - 1, start, temp, point);
	cout << start << " => " << point << endl;
	xanoi(n - 1, temp, point, start);
}

int main() {
	xanoi(3, 1, 3, 2);
}
