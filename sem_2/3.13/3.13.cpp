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
	int s = 0;
	int tmp;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			arr[i][j] = ((float)rand() / RAND_MAX) * (20 - 1) + 1;
		}
	}
	show(arr, N);
	for (int j = 0; j < N - 1; j++) {
		for (int i = 0; i < N - j - 1; i++) {
			if (arr[s][i] > arr[s][i + 1]) {
				for (int k = 0; k < N; k++) {
					tmp = arr[k][i];
					arr[k][i] = arr[k][i + 1];
					arr[k][i + 1] = tmp;
				}
			}
		}
	}
	show(arr, N);
}