#include <iostream>
using namespace std;
void show(int arr[100], int N) {
	for (int i = 0; i < N; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}
int main() {
	srand(time(0));
	int N = 5;
	int arr[100];
	int tmp[100];
	for (int i = 0; i < N; i++) {
		arr[i] = ((float)rand() / RAND_MAX) * 10;
		tmp[i] = arr[i];
	}
	show(arr, N);
	int K = 2;
	for (int i = 0; i < N; i++) {
		if (i + K >= N) arr[i + K - N] = tmp[i];
		else arr[i + K] = tmp[i];
	}
	show(arr, N);
}