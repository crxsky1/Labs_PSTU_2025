#include <iostream>
#include <iomanip> 
using namespace std;

double exactFunction(double x) {
    double arctg = 0.0;
    double term_arctg = x;
    int sign = 1;

    for (int i = 1; i <= 20; i += 2) {
        if (i == 1) {
            arctg += term_arctg;
        }
        else {
            term_arctg *= -x * x * (i - 2) / i;
            arctg += term_arctg;
        }
    }

    double y = x * x;
    double ln = 0.0;
    double term_ln = y;

    for (int i = 1; i <= 20; i++) {
        if (i == 1) {
            ln += term_ln;
        }
        else {
            if (i % 2 == 0) {
                term_ln = -term_ln * y * (i - 1) / i;
            }
            else {
                term_ln = -term_ln * y * (i - 1) / i;
            }
            ln += term_ln;
        }
    }

    return x * arctg - 0.5 * ln;
}

double sumForFixedN(double x, int n) {
    double sum = 0.0;
    double term;

    for (int k = 1; k <= n; ++k) {
        if (k == 1) {
            term = x * x / 2.0;
        }
        else {
            double multiplier = -x * x * (2 * k - 2) * (2 * k - 3) / ((2.0 * k) * (2.0 * k - 1));
            term *= multiplier;
        }
        sum += term;
    }

    return sum;
}

double sumForGivenEpsilon(double x, double epsilon) {
    double sum = 0.0;
    double term;
    int k = 1;

    term = x * x / 2.0;
    sum += term;

    while (term > epsilon || -term > epsilon) {
        k++;

        double multiplier = -x * x * (2 * k - 2) * (2 * k - 3) / ((2.0 * k) * (2.0 * k - 1));
        term *= multiplier;

        sum += term;

        if (k > 1000) {
            cout << "Достигнут лимит итераций (1000)" << endl;
            break;
        }
    }

    return sum;
}

int main() {
    setlocale(LC_ALL, "ru");
    double a = 0.1;
    double b = 0.8;
    int k = 10;
    int n = 10;
    double epsilon = 0.0001;

    double step = (b - a) / k;

    cout << "---------------------------------------------------------------------------------" << endl;
    cout << "|   x    |  Точное зн. | Сумма (n=10) | Погрешность | Сумма (eps) | Погрешность |" << endl;
    cout << "---------------------------------------------------------------------------------" << endl;

    cout << fixed << setprecision(6);

    for (int i = 0; i <= k; i++) {
        double x = a + i * step;

        double exact = exactFunction(x);

        double sum_n = sumForFixedN(x, n);

        double sum_eps = sumForGivenEpsilon(x, epsilon);

        double error_n = (exact - sum_n);
        if (error_n < 0) error_n = -error_n;

        double error_eps = (exact - sum_eps);
        if (error_eps < 0) error_eps = -error_eps;

        cout << "|" << setw(8) << x
            << "|" << setw(13) << exact
            << "|" << setw(12) << sum_n
            << "|" << setw(12) << error_n
            << "|" << setw(11) << sum_eps
            << "|" << setw(12) << error_eps << "|" << endl;
    }

    cout << "---------------------------------------------------------------------------------" << endl;

    return 0;
}