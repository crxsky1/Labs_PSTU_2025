#include <iostream>
using namespace std;


void move(int xan[][3], int N, int start, int point) {
    static int step = 1;
    cout << " step: " << step << " | " << start << " >>> " << point << endl << endl;
    step++;
    int tmp = 0;
    for (int i = 0; i < N; i++) {
        if (xan[i][start] != 0) {
            tmp = xan[i][start];
            xan[i][start] = 0;
            break;
        }
    }
    for (int i = 0; i < N + 1; i++) {
        if (i < N) {
            if (xan[i][point] != 0) {
                xan[i - 1][point] = tmp;
                break;
            }
        }
        else {
            xan[N - 1][point] = tmp;
        }


    }

}
void visualization(int xan[][3], int N) {
    for (int j = 0; j < 3; j++) {
        for (int k = 0; k < (N * 2 + 1) / 2; k++) {
            cout << " ";
        }
        cout << "|";
        for (int k = 0; k < (N * 2 + 1) / 2; k++) {
            cout << " ";
        }
        cout << "\t";
    }

    cout << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 3; j++) {

            for (int k = 0; k < (N * 2 + 1) / 2 - xan[i][j] / 2; k++) {
                cout << " ";
            }
            if (xan[i][j] == 0) {
                cout << "|";
            }
            else {
                for (int k = 0; k < xan[i][j]; k++) {
                    cout << "*";
                }
            }
            for (int k = 0; k < (N * 2 + 1) / 2 - xan[i][j] / 2; k++) {
                cout << " ";
            }
            cout << "\t";
        }
        cout << endl;
    }
    for (int j = 0; j < 3; j++) {
        for (int p = 0; p < (N * 2 + 1); p++) {
            cout << "=";
        }
        cout << "\t";
    }
    cout << endl;
    for (int j = 0; j < 3; j++) {
        for (int k = 0; k < (N * 2 + 1) / 2; k++) {
            cout << " ";
        }
        cout << j;
        for (int k = 0; k < (N * 2 + 1) / 2; k++) {
            cout << " ";
        }
        cout << "\t";
    }
    cout << endl << endl << endl;


    /*
           |
          ***
         *****
        *******
       *********
       =========
                  */
}

// n - количество колец
// start - столбец начала
// point - цель куда ложим
// temp - вспомогательный столб
void xanoi(int xan[][3], int n, int N, int start, int point, int temp) {
    if (n <= 0) return;
    xanoi(xan, n - 1, N, start, temp, point);

    move(xan, N, start, point);
    visualization(xan, N);
    // cout << start << " => " << point << endl;
    xanoi(xan, n - 1, N, temp, point, start);
}


int main() {
    const int N = 3;

    int xan[N][3];
    cout << " start position" << endl << endl;
    for (int i = 0; i < N; i++) {
        xan[i][0] = 2 * (i + 1) + 1;
        xan[i][1] = 0;
        xan[i][2] = 0;
    }
    visualization(xan, N);
    xanoi(xan, N, N, 0, 2, 1);
}