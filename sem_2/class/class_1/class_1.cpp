#include <iostream>

using namespace std;


class MyClass {
private:
	int first;
	int second;

	double num;

public:
	MyClass(int f, int s) {
		first = f;
		second = s;

		num = second;

		while (num >= 1) {
			// cout << num << endl;
			num /= 10.0;
		}
		num += first;

		cout /*<< endl << endl*/ << num << endl;
	}
	double multiply(int k) {
		return num * k;
	}

};


int main() {
	MyClass number(10, 155);

	cout << number.multiply(10);
}