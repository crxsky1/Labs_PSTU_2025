#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;
int splitToSeries(const char* inputFile, const char* outputFile1, const char* outputFile2) {
    ifstream in(inputFile);
    ofstream out1(outputFile1);
    ofstream out2(outputFile2);
    if (!in.is_open()) {
        cout << "Ошибка открытия файла!" << endl;
        return 0;
    }
    int prev, curr;
    int seriesCount = 0;
    bool toFirst = true;
    in >> prev;
    out1 << prev << " ";
    seriesCount++;
    while (in >> curr) {
        if (curr < prev) {
            seriesCount++;
            toFirst = !toFirst;
        }
        if (toFirst) {
            out1 << curr << " ";
        }
        else
        {
            out2 << curr << " ";
        }
        prev = curr;
    }
    in.close();
    out1.close();
    out2.close();
    return seriesCount;
}
void getFibonNumbers(int n, int& f1, int& f2) {
    f1 = 1;
    f2 = 1;
    while (f1 + f2 <= n) {
        int next = f1 + f2;
        f1 = f2;
        f2 = next;
    }
}
void bubbleSort(int arr[], int start, int end) {
    for (int i = start; i < end - 1; i++) {
        for (int j = start; j < end - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
void polyphaseSort(int arr[], int n) {
    if (n <= 1) return;
    int f1, f2;
    getFibonNumbers(n, f1, f2);
    int size1 = f2;
    int size2 = n - f2;
    bubbleSort(arr, 0, size1);
    bubbleSort(arr, size1, n);
    int* temp = new int[n];
    int i = 0, k = 0;
    int j = size1;
    while (i < size1 && j < n) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        }
        else {
            temp[k++] = arr[j++];
        }
    }
    while (i < size1) {
        temp[k++] = arr[i++];
    }
    while (j < n) {
        temp[k++] = arr[j++];
    }
    for (int i = 0; i < n; i++) {
        arr[i] = temp[i];
    }
    delete[] temp;
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
    int arr[] = { 41, 8, 15, 24, 2, 1, 12, 7, 5, 3, 9, 6 };
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << "Исходный массив: ";
    printArr(arr, n);
    int f1, f2;
    getFibonNumbers(n, f1, f2);
    cout << "Числа Фибоначчи: " << f1 << ", " << f2 << endl;
    cout << "Разбиение: " << f2 << "+" << n - f2 << endl;
    polyphaseSort(arr, n);
    cout << "Отсортированный массив: ";
    printArr(arr, n);
    return 0;
}