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

int partitionHoare(int arr[], int low, int high) {
	// часто берут центральный или первый элемент

	int pI = (high + low) / 2;
	int pivot = arr[pI];
	int i = low - 1; // левый индекс на 1 меньше левой границы
	int j = high + 1; // правый индекс на 1 больше правой границы

	while (true)
	{
		do {
			i++;
		} while (arr[i] < pivot);

		do {
			j--;
		} while (arr[j] > pivot);

		if (i >= j) {
			return j;
		}

		if (pI == j) pI = i;
		else if (pI == i) pI = j;

		swap(arr[i], arr[j]);
	}
}

void quickSortHoare(int arr[], int low, int high) {
	if (low < high) {
		int pI = partitionHoare(arr, low, high);

		quickSortHoare(arr, low, pI);
		quickSortHoare(arr, pI + 1, high);
	}
}

int main() {
	setlocale(LC_ALL, "ru");
	int size = 10;

	int arr[10] = { 1, 7, 1, 9, 5, 3, 5, 4, 8, 5 };
	draw(arr, size);


	quickSortHoare(arr, 0, 9);
	draw(arr, size);
}