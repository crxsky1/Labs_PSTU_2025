#include <iostream>
using namespace std;

class Pair {
private:
    int first;
    double second;

public:
    Pair(int f, double s) : first(f), second(s) {}

    void print() const {
        cout << first << ":" << second << endl;
    }

    bool operator==(const Pair& pair) const {
        return (pair.first == first) && (pair.second == second);
    }

    bool operator!=(const Pair& pair) const {
        return (pair.first != first) && (pair.second != second);
    }


    Pair operator-(int num) const {
        return Pair(first - num, second);
    }

    Pair operator-(double num) const {
        return Pair(first, second - num);
    }

    Pair operator+(int num) const {
        return Pair(first + num, second);
    }

    Pair operator+(double num) const {
        return Pair(first, second + num);
    }
};

int main() {
    Pair pair1(10, 3.134);
    Pair pair2(10, 3.134);
    Pair pair3(14, 3.0);

    cout << "pair1: "; pair1.print();
    cout << "pair2: "; pair2.print();
    cout << "pair3: "; pair3.print();

    cout << endl;

    cout << "pair1 == pair2  " << (pair1 == pair2) << endl;
    cout << "pair1 == pair3  " << (pair1 == pair3) << endl;

    cout << endl;

    (pair2 - 10).print();
    pair2 = ((pair3 - 4) + 0.134);

    cout << "new pair2: "; pair2.print();

    cout << "pair2 == pair1  " << (pair2 == pair1) << endl;

}