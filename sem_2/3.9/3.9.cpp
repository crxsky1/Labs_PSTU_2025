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
	for (int i = 0; i < N; i++) {
		arr[i] = ((float)rand() / RAND_MAX) * 20;
	}
	show(arr, N);
	for (int i = 0; i < N; i++) {
		if (arr[i] % 2 != 0) {
			for (int j = i; j < N; j++) {
				arr[j] = arr[j + 1];
			}
			N--;
		}
	}
	show(arr, N);
}