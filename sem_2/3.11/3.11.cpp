#include <iostream>
using namespace std;
void show(int arr[4][4], int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << arr[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}
int main() {
	srand(time(0));
	const int N = 4;
	int arr[N][N];
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			arr[i][j] = ((float)rand() / RAND_MAX) * 20;
		}
	}
	show(arr, N);
	int tmp;
	for (int i = 0; i < N; i++) {
		arr[i][i] = 0;
	}
	show(arr, N);
}