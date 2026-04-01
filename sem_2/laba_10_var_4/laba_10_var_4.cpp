#include <iostream>
#include <windows.h>

using namespace std;

void printArray(int* arr, int size, const string& message) {
    cout << message << endl;
    if (size == 0) {
        cout << "Массив пуст" << endl;
        return;
    }
    for (int i = 0; i < size; i++) {
        cout << "arr[" << i << "] = " << arr[i] << endl;
    }
    cout << endl;
}

int* deleteElement(int* arr, int& size, int position) {
    if (position < 0 || position >= size) {
        cout << "Ошибка: элемента с номером " << position << " не существует!" << endl;
        cout << "Доступные номера: от 0 до " << size - 1 << endl;
        return arr;
    }

    int* newArr = new int[size - 1];

    for (int i = 0; i < position; i++) {
        newArr[i] = arr[i];
    }

    for (int i = position + 1; i < size; i++) {
        newArr[i - 1] = arr[i];
    }

    delete[] arr;

    size--;

    cout << "Элемент с номером " << position << " удален." << endl;
    return newArr;
}

void addToElements(int* arr, int size, int startPosition, int value) {
    if (startPosition < 0 || startPosition >= size) {
        cout << "Ошибка: начальная позиция " << startPosition << " не существует!" << endl;
        cout << "Доступные номера: от 0 до " << size - 1 << endl;
        return;
    }

    cout << "Добавление значения " << value << " к элементам, начиная с номера " << startPosition << ":" << endl;

    for (int i = startPosition; i < size; i++) {
        int oldValue = arr[i];
        arr[i] += value;
        cout << "arr[" << i << "]: " << oldValue << " + " << value << " = " << arr[i] << endl;
    }
    cout << endl;
}

int* inputArray(int& size) {
    cout << "Введите размер массива: ";
    cin >> size;

    int* arr = new int[size];

    cout << "Введите элементы массива:" << endl;
    for (int i = 0; i < size; i++) {
        cout << "arr[" << i << "] = ";
        cin >> arr[i];
    }

    return arr;
}

int* generateRandomArray(int& size) {
    cout << "Введите размер массива: ";
    cin >> size;

    int* arr = new int[size];

    cout << "Сгенерированный массив:" << endl;
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 201 - 100;
        cout << "arr[" << i << "] = " << arr[i] << endl;
    }
    cout << endl;

    return arr;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    srand(time(NULL));

    int* arr = nullptr;
    int size = 0;
    int choice;

    cout << "=== ОДНОМЕРНЫЙ МАССИВ ===" << endl;
    cout << endl;

    cout << "Выберите способ создания массива:" << endl;
    cout << "1. Ввод с клавиатуры" << endl;
    cout << "2. Случайные числа" << endl;
    cout << "Ваш выбор: ";
    cin >> choice;

    if (choice == 1) {
        arr = inputArray(size);
    }
    else {
        arr = generateRandomArray(size);
    }

    printArray(arr, size, "Исходный массив:");

    int operation;
    do {
        cout << "\n=== МЕНЮ ===" << endl;
        cout << "1. Удалить элемент с заданным номером" << endl;
        cout << "2. Добавить значение к элементам, начиная с заданного номера" << endl;
        cout << "3. Вывести текущий массив" << endl;
        cout << "4. Создать новый массив" << endl;
        cout << "0. Выход" << endl;
        cout << "Ваш выбор: ";
        cin >> operation;

        switch (operation) {
        case 1: {
            if (size == 0) {
                cout << "Массив пуст! Удаление невозможно." << endl;
                break;
            }

            int position;
            cout << "Введите номер элемента для удаления (0-" << size - 1 << "): ";
            cin >> position;

            arr = deleteElement(arr, size, position);
            printArray(arr, size, "Массив после удаления:");
            break;
        }

        case 2: {
            if (size == 0) {
                cout << "Массив пуст! Операция невозможна." << endl;
                break;
            }

            int startPosition, value;
            cout << "Введите начальный номер элемента (0-" << size - 1 << "): ";
            cin >> startPosition;
            cout << "Введите значение для добавления: ";
            cin >> value;

            addToElements(arr, size, startPosition, value);
            printArray(arr, size, "Массив после добавления:");
            break;
        }

        case 3: {
            printArray(arr, size, "Текущий массив:");
            break;
        }

        case 4: {
            delete[] arr;

            cout << "\nВыберите способ создания нового массива:" << endl;
            cout << "1. Ввод с клавиатуры" << endl;
            cout << "2. Случайные числа" << endl;
            cout << "Ваш выбор: ";
            cin >> choice;

            if (choice == 1) {
                arr = inputArray(size);
            }
            else {
                arr = generateRandomArray(size);
            }

            printArray(arr, size, "Новый массив:");
            break;
        }

        case 0:
            cout << "Программа завершена." << endl;
            break;

        default:
            cout << "Неверный выбор! Попробуйте снова." << endl;
        }

    } while (operation != 0);

    if (arr != nullptr) {
        delete[] arr;
    }

    system("pause");
    return 0;
}