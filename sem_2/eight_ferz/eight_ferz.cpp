
#include <iostream>
using namespace std;

const int N = 8;

void vizualization(int arr[N][N]) {

	cout << "\t";
	for (int i = 0; i < N; i++) {
		cout << "  " << i << " ";
	}
	// cout << "  columns";
	cout << endl;

	for (int i = 0; i < N; i++) {
		cout << "\t";
		for (int j = 0; j < N; j++) {
			cout << "----";
		}
		cout << "-" << endl;
		cout << "     " << i << "\t";

		for (int j = 0; j < N; j++) {
			cout << "| ";
			if (arr[i][j] == 1) cout << "F ";
			else cout << "  ";
		}
		cout << "|" << endl;
	}
	// cout << "   rows";
	cout << "\t";
	for (int j = 0; j < N; j++) {
		cout << "----";
	}
	cout << "-" << endl << endl << endl;
}

bool canSetFerz(int arr[N][N], int x, int y) {
	for (int row = 0; row < y; row++) {
		for (int col = 0; col < N; col++) {
			if (arr[row][col] == 1) {
				if ((x == col) || (y == row) || (x - y == col - row) || ((N - x) - y == (N - col) - row))
					return 0;
			}
		}
	}
	return 1;
}

void eightFerz(int arr[N][N], int row) {
	static int count = 0;
	for (int col = 0; col < N; col++) {
		if (canSetFerz(arr, col, row)) {
			if (row == N - 1) {
				arr[row][col] = 1;
				vizualization(arr);
				arr[row][col] = 0;
				count++;
			}
			else {
				arr[row][col] = 1;
				eightFerz(arr, row + 1);
				arr[row][col] = 0;
			}
		}
	}
	if (row == 0) cout << "\ttotal boards: " << count << endl << endl << endl;
}


int main() {
	int arr[N][N];

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			arr[i][j] = 0;
		}
	}
	eightFerz(arr, 0);



}
