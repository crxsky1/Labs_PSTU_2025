# include <iostream>
# include <Windows.h>
using namespace std;
int partitionLomuto(int arr[], int low, int high) {
	int pivot = arr[high];
	int i = low - 1;
	for (int j = low; j <= high - 1; j++) {
		if (arr[j] <= pivot) {
			i++;
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i + 1], arr[high]);
	return i + 1;
}
void quickSortLomuto(int arr[], int low, int high) {
	if (low < high) {
		int pi = partitionLomuto(arr, low, high);
		quickSortLomuto(arr, low, pi - 1);
		quickSortLomuto(arr, pi + 1, high);
	}
}
void printArr(int arr[], int n) {
	cout << "[";
	for (int i = 0; i < n; i++) {
		cout << arr[i];
		if (i < n - 1) cout << ", ";
	}
	cout << "]" << endl;
}
int main() {
	setlocale(LC_ALL, "ru");
	int arr[] = { 5, 2, 4, 6, 1, 3, 9, 7, 8, 0 };
	int n = sizeof(arr) / sizeof(arr[0]);
	cout << "Исходный массив: ";
	printArr(arr, n);
	quickSortLomuto(arr, 0, n - 1);
	cout << "Отсортированный массив: ";
	printArr(arr, n);
	return 0;
}