#include <iostream>
#include <cstring>
#include <windows.h>
using namespace std;
int* nativeSearch(const char* text, const char* pattern, int& outCount) {
	outCount = 0;
	int n = strlen(text);
	int m = strlen(pattern);
	if (m == 0 || m > n) return nullptr;
	int* tmpEntr = new int[n - m + 1];
	for (int i = 0; i <= n - m; i++) {
		int j = 0;
		while (j < m && text[i + j] == pattern[j]) {
			j++;
		}
		if (j == m) {
			tmpEntr[outCount] = i;
			outCount++;
		}
	}
	if (outCount == 0) {
		delete[] tmpEntr;
		return nullptr;
	}
	int* properEntr = new int[outCount];
	for (int i = 0; i < outCount; i++) {
		properEntr[i] = tmpEntr[i];
	}
	delete[] tmpEntr;
	return properEntr;
}
int main() {
	setlocale(LC_ALL, "ru");
	const char* text = "AABAACAADAABAABA";
	const char* pattern = "AABA";
	int count = 0;
	int* res = nativeSearch(text, pattern, count);
	if (res != nullptr) {
		cout << "Найдено " << count << " вхождений по индексам: " << endl;
		for (int i = 0; i < count; i++) {
			cout << res[i] << " ";
		}
		cout << endl;
		delete[] res;
	}
	else cout << "Вхождений не найдено!" << endl;
	return 0;
}