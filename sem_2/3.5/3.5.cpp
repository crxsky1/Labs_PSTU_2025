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

	int N = 10;
	int arr[100];


	for (int i = 0; i < N; i++) {
		arr[i] = ((float)rand() / RAND_MAX) * 20;
	}
	show(arr, N);
	
	int mx = arr[0];
	for (int i = 1; i < N; i++) {
		if (arr[i] > mx) mx = arr[i];
	}
	cout << endl << mx;
}
