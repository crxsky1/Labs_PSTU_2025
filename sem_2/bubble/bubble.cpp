#include<iostream>
using namespace std;

int main() {
	const int N = 5;
	int arr[N] = { 3,2,4,1,5 };
	int tmp;

	for (int k = 0; k < N - 1; k++) {
		for (int i = 0; i < N - 1; i++) {
			if (arr[i] < arr[i + 1]) {

			}
			else {
				tmp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp;

			}
			for (int j = 0; j < N; j++) {
				cout << arr[j];
			}
			cout << endl;
		}
	}




}