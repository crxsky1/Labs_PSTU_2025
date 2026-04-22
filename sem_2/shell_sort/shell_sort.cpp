#include <iostream>
using namespace std;

void draw(int arr[], int size) {
	int max = arr[0];

	for (int i = 1; i < size; i++) { if (arr[i] > max) { max = arr[i]; } }

	for (int i = max; i >= 0; i--) {
		cout << " ";
		for (int j = 0; j < size; j++) {

			if (arr[j] > i) {
				cout << "[ ] ";
			}
			else {
				cout << "    ";
			}
		}
		cout << endl;
	}
	for (int i = 0; i < size; i++) {
		cout << "  " << arr[i] << " ";
	}
	cout << endl;
}

void shellSort(int arr[], int size) {
	for (int step = size / 2; step > 0; step /= 2) {
		for (int i = step; i < size; i++) {
			int temp = arr[i];
			int j;
			for (j = i; j >= step && arr[j - step] > temp; j -= step) {
				arr[j] = arr[j - step];
			}
			arr[j] = temp;
		}
	}
}


int main() {
	setlocale(LC_ALL, "ru");
	int size = 10;

	int arr[10] = { 1, 7, 1, 9, 5, 3, 5, 4, 8, 5 };
	draw(arr, size);

	shellSort(arr, size);
	draw(arr, size);
}