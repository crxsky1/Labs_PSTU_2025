#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

double exact(double x) {
    return x * atan(x) - 0.5 * log(1 + x * x);
}

double sumN(double x, int n) {
    double sum = x * x / 2, term = sum;
    for (int k = 2; k <= n; k++) {
        term *= -x * x * (2 * k - 3) * (2 * k - 2) / ((2 * k - 1) * 2 * k);
        sum += term;
    }
    return sum;
}

double sumEps(double x, double eps) {
    double sum = x * x / 2, term = sum;
    for (int k = 2; fabs(term) > eps; k++) {
        term *= -x * x * (2 * k - 3) * (2 * k - 2) / ((2 * k - 1) * 2 * k);
        sum += term;
        if (k > 1000) break;
    }
    return sum;
}

int main() {
    setlocale(LC_ALL, "ru");
    cout << fixed << setprecision(6);
    cout << "|   x   | Точное  |Sum(n=10) | Погрешн | Sum(eps)| Погрешн|\n";

    for (double x = 0.1; x <= 0.801; x += 0.07) {
        double ex = exact(x);
        double s10 = sumN(x, 10);
        double seps = sumEps(x, 1e-4);
        printf("|%6.3f |%8.5f |%9.6f |%7.6f |%8.6f |%7.6f|\n",
            x, ex, s10, fabs(ex - s10), seps, fabs(ex - seps));
    }
}