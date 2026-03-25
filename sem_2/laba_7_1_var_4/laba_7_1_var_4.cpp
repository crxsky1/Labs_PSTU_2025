#include <iostream>
#include <cmath>
using namespace std;

struct Complex {
    double real;
    double imag;
};

int subtract(int a, int b) {
    return a - b;
}

Complex subtract(Complex c1, Complex c2) {
    Complex result;
    result.real = c1.real - c2.real;
    result.imag = c1.imag - c2.imag;
    return result;
}

void printComplex(Complex c, const char* name) {
    cout << name << " = ";
    if (c.imag >= 0) {
        cout << c.real << " + " << c.imag << "i";
    }
    else {
        cout << c.real << " - " << -c.imag << "i";
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "=== ПЕРЕГРУЖЕННЫЕ ФУНКЦИИ ДЛЯ ВЫЧИТАНИЯ ===" << endl;
    cout << endl;

    cout << "а) Вычитание целых чисел:" << endl;
    cout << "-------------------------" << endl;

    int int1, int2;
    cout << "Введите первое целое число: ";
    cin >> int1;
    cout << "Введите второе целое число: ";
    cin >> int2;

    int intResult = subtract(int1, int2);
    cout << int1 << " - " << int2 << " = " << intResult << endl;
    cout << endl;

    cout << "б) Вычитание комплексных чисел:" << endl;
    cout << "-------------------------------" << endl;

    Complex complex1, complex2;

    cout << "Введите первое комплексное число (действительная и мнимая части): ";
    cin >> complex1.real >> complex1.imag;

    cout << "Введите второе комплексное число (действительная и мнимая части): ";
    cin >> complex2.real >> complex2.imag;

    Complex complexResult = subtract(complex1, complex2);

    cout << endl;
    printComplex(complex1, "Первое число");
    printComplex(complex2, "Второе число");
    cout << endl;

    cout << "Результат вычитания: ";
    printComplex(complexResult, "complex1 - complex2");

    return 0;
}