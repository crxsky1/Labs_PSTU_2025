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
	int tmp;
	for (int i = 0; i < N; i++) {
		arr[i] = ((float)rand() / RAND_MAX) * 20;
	}
	show(arr, N);
	for (int i = 0; i < N; i++) {
		if (arr[i] % 2 == 0) {
			for (int j = N; j >= i; j--) {
				arr[j + 1] = arr[j];
			}
			arr[i] = -1;
			N++;
			i++;
		}
	}
	show(arr, N);
}