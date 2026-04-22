# include <iostream>
# include <Windows.h>
using namespace std;
int linearSearch(int arr[], int n, int x) {
	for (int i = 0; i < n; i++) {
		if (arr[i] == x) return i;
	}
	return -1;
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
	int arr[] = { 32, 5, 66, 12, 97, 10, 2, 7, 88, 42 };
	int n = sizeof(arr) / sizeof(arr[0]);
	int x = 10;
	cout << "Массив: ";
	printArr(arr, n);
	int res = linearSearch(arr, n, x);
	if (res == -1) cout << "Элемент " << x << " не найден" << endl;
	else cout << "Элемент " << x << " найден по индексу " << res << endl;
	return 0;
}