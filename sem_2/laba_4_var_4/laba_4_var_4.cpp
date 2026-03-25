#include <iostream>
#include <ctime>
#include <cmath>

using namespace std;

void printArray(int* arr, int size, const string& message) {
    cout << message << endl;
    for (int i = 0; i < size; i++) {
        cout << "arr[" << i << "] = " << arr[i] << endl;
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "ru");

    srand(time(nullptr));

    int n;
    cout << "Введите размер массива: ";
    cin >> n;

    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 201 - 100;
    }

    printArray(arr, n, "Исходный массив:");

    cout << "Удаление элементов с индексами, кратными 3..." << endl;

    int newSize = 0;
    for (int i = 0; i < n; i++) {
        if (i % 3 != 0) {
            newSize++;
        }
    }

    int* tempArr = new int[newSize];
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (i % 3 != 0) {
            tempArr[j] = arr[i];
            j++;
        }
    }

    delete[] arr;
    arr = tempArr;
    n = newSize;

    printArray(arr, n, "Массив после удаления элементов с индексами, кратными 3:");

    cout << "Добавление элементов после каждого отрицательного элемента..." << endl;

    int negativeCount = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] < 0) {
            negativeCount++;
        }
    }

    int newSize2 = n + negativeCount;
    int* finalArr = new int[newSize2];

    int k = 0;
    for (int i = 0; i < n; i++) {
        finalArr[k] = arr[i];
        k++;

        if (arr[i] < 0) {
            int newValue;
            if (i > 0) {
                newValue = abs(arr[i - 1] + 1);
            }
            else {
                newValue = abs(arr[i] + 1);
            }
            finalArr[k] = newValue;
            k++;
        }
    }

    delete[] arr;
    arr = finalArr;
    n = newSize2;

    printArray(arr, n, "Итоговый массив:");

    delete[] arr;

    return 0;
}