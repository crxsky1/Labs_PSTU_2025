#include <iostream>
#include <ctime>
#include <cmath>

using namespace std;

void inputSizes(int& rows, int& cols) {
    cout << "Введите количество строк: ";
    cin >> rows;
    cout << "Введите количество столбцов: ";
    cin >> cols;
}

void fillRandomArray(int** arr, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            arr[i][j] = rand() % 201 - 100;
        }
    }
}

void printArray(int** arr, int rows, int cols, const string& message) {
    cout << message << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << arr[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

int** allocateMemory(int rows, int cols) {
    int** arr = new int* [rows];
    for (int i = 0; i < rows; i++) {
        arr[i] = new int[cols];
        for (int j = 0; j < cols; j++) {
            arr[i][j] = 0;
        }
    }
    return arr;
}

void freeMemory(int** arr, int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] arr[i];
    }
    delete[] arr;
}

int** deleteRows(int** arr, int& rows, int cols, int A, int B) {
    if (A < 0) A = 0;
    if (B >= rows) B = rows - 1;
    if (A > B) {
        cout << "Ошибка: A должно быть меньше или равно B" << endl;
        return arr;
    }

    int deleteCount = B - A + 1;
    int newRows = rows - deleteCount;

    if (newRows == 0) {
        cout << "Все строки удалены" << endl;
        freeMemory(arr, rows);
        return nullptr;
    }

    int** newArr = allocateMemory(newRows, cols);

    int newRowIndex = 0;
    for (int i = 0; i < rows; i++) {
        if (i >= A && i <= B) {
            continue;
        }
        for (int j = 0; j < cols; j++) {
            newArr[newRowIndex][j] = arr[i][j];
        }
        newRowIndex++;
    }

    freeMemory(arr, rows);

    rows = newRows;

    return newArr;
}

void replaceMissingWithZero(int** arr, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (arr[i][j] == 0) {
                arr[i][j] = 0;
            }
        }
    }
    cout << "Недостающие элементы заменены на 0" << endl;
}

int** shiftRowsAndReplace(int** arr, int& rows, int cols, int A, int B) {
    if (A < 0) A = 0;
    if (B >= rows) B = rows - 1;
    if (A > B) {
        cout << "Ошибка: A должно быть меньше или равно B" << endl;
        return arr;
    }

    int deleteCount = B - A + 1;
    int newRows = rows - deleteCount;

    int** tempArr = allocateMemory(rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            tempArr[i][j] = arr[i][j];
        }
    }

    int shift = 0;
    for (int i = 0; i < rows; i++) {
        if (i >= A && i <= B) {
            shift++;
        }
        else {
            if (shift > 0) {
                for (int j = 0; j < cols; j++) {
                    tempArr[i - shift][j] = tempArr[i][j];
                }
            }
        }
    }

    int** newArr = allocateMemory(newRows, cols);

    for (int i = 0; i < newRows; i++) {
        for (int j = 0; j < cols; j++) {
            newArr[i][j] = tempArr[i][j];
        }
    }

    for (int i = 0; i < newRows; i++) {
        for (int j = 0; j < cols; j++) {
        }
    }

    freeMemory(tempArr, rows);
    freeMemory(arr, rows);

    rows = newRows;

    return newArr;
}

int main() {
    setlocale(LC_ALL, "ru");
    srand(time(nullptr));

    int rows, cols;
    inputSizes(rows, cols);

    int** arr = allocateMemory(rows, cols);

    fillRandomArray(arr, rows, cols);

    printArray(arr, rows, cols, "Исходный массив:");

    int A, B;
    cout << "Введите номер первой строки для удаления (A): ";
    cin >> A;
    cout << "Введите номер последней строки для удаления (B): ";
    cin >> B;

    arr = deleteRows(arr, rows, cols, A, B);

    if (arr != nullptr) {
        printArray(arr, rows, cols, "Массив после удаления строк с номерами от A до B:");

        replaceMissingWithZero(arr, rows, cols);

        printArray(arr, rows, cols, "Итоговый массив:");

        freeMemory(arr, rows);
    }

    return 0;
}