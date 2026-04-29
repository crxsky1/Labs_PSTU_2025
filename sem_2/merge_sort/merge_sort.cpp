#include <iostream>
#include <windows.h>
using namespace std;
void merge(int arr[], int start, int mid, int end) {
	int leftRange = mid - start + 1;
	int rightRange = end - mid;
	int* leftArr = new int[leftRange];
	int* rightArr = new int[rightRange];
	for (int i = 0; i < leftRange; i++) {
		leftArr[i] = arr[start + i];
	}
	for (int j = 0; j < rightRange; j++) {
		rightArr[j] = arr[mid + 1 + j];
	}
	int leftIndex = 0, rightIndex = 0, mergeIndex = start;
	while (leftIndex < leftRange && rightIndex < rightRange) {
		if (leftArr[leftIndex] <= rightArr[rightIndex]) {
			arr[mergeIndex] = leftArr[leftIndex];
			leftIndex++;
		}
		else {
			arr[mergeIndex] = rightArr[rightIndex];
			rightIndex++;
		}
		mergeIndex++;
	}
	while (leftIndex < leftRange) {
		arr[mergeIndex] = leftArr[leftIndex];
		leftIndex++;
		mergeIndex++;
	}
	while (rightIndex < rightRange) {
		arr[mergeIndex] = rightArr[rightIndex];
		rightIndex++;
		mergeIndex++;
	}
	delete[] leftArr;
	delete[] rightArr;
}
void mergeSort(int arr[], int start, int end) {
	if (start >= end) return;
	int mid = start + (end - start) / 2;
	mergeSort(arr, start, mid);
	mergeSort(arr, mid + 1, end);
	merge(arr, start, mid, end);
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
	int arr[] = { 38, 27, 43, 3, 9, 82, 10, 5, 1, 19 };
	int n = sizeof(arr) / sizeof(arr[0]);
	cout << "Исходный массив: ";
	printArr(arr, n);
	mergeSort(arr, 0, n - 1);
	cout << "Отсортированный массив: ";
	printArr(arr, n);
	return 0;
}