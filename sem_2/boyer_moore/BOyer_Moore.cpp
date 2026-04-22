#include <iostream>
#include <string>

using namespace std;

/*
таблицв сдвигов
	 h - 4
	 e - 3
	 l - 1
	 o - 5 - для последнего количество букв в подстроке

	lo_loello_o_hello
	hello
	  ||| o == o
	  || l == l
	  | l != _   =>   сдвигаемся на значение в таблице для l (на 1)

	lo_loello_o_hello
	 hello
		 | o != e   =>   сдвигаемся на значение для о (на 5)


	lo_loello_o_hello
		  hello
			 | l != _   =>   сдвиг на 1


	lo_loello_o_hello
		   hello
			   | o != _   =>   сдвиг на 5

	lo_loello_o_hello
				hello
	  !!!найдено!!!

*/

struct Shift {
	char letter;
	int shift = 0;
};

// Алгоритм Бойера-Мура-Хорствула
int BMHSearch(string str, string substr) {
	int size = substr.size();
	Shift* tsh = new Shift[size];

	for (int i = 0; i < size - 1; i++) {
		tsh[i].letter = substr[i];
		tsh[i].shift = size - 1 - i;
	}
	tsh[size - 1].letter = substr[size - 1];
	tsh[size - 1].shift = size;

	cout << "таблица сдвигов" << endl;
	for (int i = 0; i < size; i++) { cout << "     " << tsh[i].letter << " - " << tsh[i].shift << endl; }



	int idx = 0;
	while (idx + size - 1 < str.size()) {
		for (int i = size - 1; i >= 0; i--) {
			cout << endl << str << endl;
			for (int i = 0; i < idx; i++) { cout << " "; }
			cout << substr << endl;
			cout << "  " << substr[i] << " " << str[i + idx] << endl;


			if (substr[i] == str[i + idx]) {
				if (i == 0) {
					cout << "ответ найден" << endl;
					delete[] tsh;
					return idx;
				}
			}
			else {
				for (int j = size - 1; j >= -1; j--) {
					if (j == -1) {
						cout << " += " << size << " " << "idx = " << idx << endl << endl;
						idx += size;
					}
					else if (str[i + idx] == tsh[j].letter) {
						idx += tsh[j].shift;
						cout << " += " << tsh[j].shift << " " << "idx = " << idx << endl << endl;
						break;
					}
				}
				break;
			}
		}
	}

	delete[] tsh;
	return -1;
}



int main() {
	setlocale(LC_ALL, "ru");

	string str = "lo_loello_o_hello";
	string substr = "hello";

	cout << "     " << BMHSearch(str, substr);
}