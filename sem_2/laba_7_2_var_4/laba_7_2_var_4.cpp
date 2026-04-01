#include <iostream>

using namespace std;

int sum() {
    return 0;
}

template<typename... Args>
int sum(int a, int b, Args... args) {
    return a * b + sum(args...);
}

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "=== ФУНКЦИЯ SUM С ПЕРЕМЕННЫМ ЧИСЛОМ ПАРАМЕТРОВ (шаблоны) ===" << endl;
    cout << "Формула: S = a1*a2 + a3*a4 + a5*a6 + ..." << endl;
    cout << endl;

    cout << "1) Вызов с 8 параметрами:" << endl;
    int result1 = sum(2, 3, 4, 5, 6, 7, 8, 9);
    cout << "   sum(2,3,4,5,6,7,8,9) = ";
    cout << "(2*3) + (4*5) + (6*7) + (8*9) = ";
    cout << "6 + 20 + 42 + 72 = " << result1 << endl;
    cout << endl;

    cout << "2) Вызов с 10 параметрами:" << endl;
    int result2 = sum(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
    cout << "   sum(1,2,3,4,5,6,7,8,9,10) = ";
    cout << "(1*2) + (3*4) + (5*6) + (7*8) + (9*10) = ";
    cout << "2 + 12 + 30 + 56 + 90 = " << result2 << endl;
    cout << endl;

    cout << "3) Вызов с 12 параметрами:" << endl;
    int result3 = sum(1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6);
    cout << "   sum(1,1,2,2,3,3,4,4,5,5,6,6) = ";
    cout << "(1*1) + (2*2) + (3*3) + (4*4) + (5*5) + (6*6) = ";
    cout << "1 + 4 + 9 + 16 + 25 + 36 = " << result3 << endl;

    return 0;
}