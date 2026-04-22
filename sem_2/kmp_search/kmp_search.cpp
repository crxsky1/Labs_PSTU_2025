#include <iostream>
#include <cstring>
#include <windows.h>
using namespace std;
void computePrefix(const char* pattern, int m, int* lps) {
	int lenght = 0;
	lps[0] = 0;
	int i = 1;
	while (i < m) {
		if (pattern[i] == pattern[lenght]) {
			lenght++;
			lps[i] = lenght;
			i++;
		}
		else {
			if (lenght != 0) {
				lenght = lps[lenght - 1];
			}
			else {
				lps[i] = 0;
				i++;
			}
		}
	}
}
int* KMPsearch(const char* text, const char* pattern, int& outCount) {
	outCount = 0;
	int n = strlen(text);
	int m = strlen(pattern);
	if (m == 0 || m > n) return nullptr;
	int* lps = new int[m];
	computePrefix(pattern, m, lps);
	int* tmpEntr = new int[n];
	int i = 0, j = 0;
	while (i < n) {
		if (pattern[j] == text[i]) {
			i++;
			j++;
		}
		if (j == m) {
			tmpEntr[outCount] = i - j;
			outCount++;
			j = lps[j - 1];
		}
		else if (i < n && pattern[j] != text[i]) {
			if (j != 0) j = lps[j - 1];
			else i++;
		}
	}
	delete[] lps;
	if (outCount == 0) {
		delete[] tmpEntr;
		return nullptr;
	}
	int* result = new int[outCount];
	for (int i = 0; i < outCount; i++) {
		result[i] = tmpEntr[i];
	}
	delete[] tmpEntr;
	return result;
}
void printArr(int arr[], int n) {
	for (int i = 0; i < n; i++) {
		cout << arr[i];
		if (i < n - 1) cout << ", ";
	}
}
int main() {
	setlocale(LC_ALL, "ru");
	const char* text = "ABABDABACDABABCABAB";
	const char* pattern = "ABABCABAB";
	int count = 0;
	int* matches = KMPsearch(text, pattern, count);
	if (matches != nullptr) {
		cout << "Найдено " << count << " совпадений по индексам: ";
		printArr(matches, count);
		cout << endl;
	}
	else cout << "Совпадений не найдено!" << endl;
	return 0;
}