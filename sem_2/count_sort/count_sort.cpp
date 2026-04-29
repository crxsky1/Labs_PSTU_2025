#include <iostream>
#include <windows.h>
using namespace std;
void countingSort(int arr[], int n) {
	if (n <= 1) return;
	int maxVal = arr[0];
	for (int i = 1; i < n; i++) {
		if (arr[i] > maxVal) maxVal = arr[i];
	}
	int* count = new int[maxVal + 1]();
	for (int i = 0; i < n; i++) {
		count[arr[i]]++;
	}
	for (int i = 1; i <= maxVal; i++) {
		count[i] += count[i - 1];
	}
	int* output = new int[n];
	for (int i = n - 1; i >= 0; i--) {
		output[count[arr[i]] - 1] = arr[i];
		count[arr[i]]--;
	}
	for (int i = 0; i < n; i++) {
		arr[i] = output[i];
	}
	delete[] count;
	delete[] output;
}
void printArray(int arr[], int n) {
	cout << "[";
	for (int i = 0; i < n; i++) {
		cout << arr[i];
		if (i < n - 1) cout << ", ";
	}
	cout << "]" << endl;
}
int main() {
	setlocale(LC_ALL, "ru");
	int arr[] = { 2, 5, 3, 0, 2, 3, 2, 0, 3 };
	int n = sizeof(arr) / sizeof(arr[0]);
	cout << "Исходный массив: ";
	printArray(arr, n);
	countingSort(arr, n);
	cout << "Отсортированный массив: ";
	printArray(arr, n);
	return 0;
}