#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;
int splitToSeries(const char* inputFile, const char* outputFile1, const char* outputFile2) {
	ifstream in(inputFile);
	ofstream out1(outputFile1);
	ofstream out2(outputFile2);
	if (!in.is_open()) {
		cout << "Ошибка открытия файла!" << endl;
		return 0;
	}
	int prev, curr;
	int seriesCount = 0;
	bool toFirst = true;
	in >> prev;
	out1 << prev << " ";
	seriesCount++;
	while (in >> curr) {
		if (curr < prev) {
			seriesCount++;
			toFirst = !toFirst;
		}
		if (toFirst) {
			out1 << curr << " ";
		}
		else out2 << curr << " ";
		prev = curr;
	}
	in.close();
	out1.close();
	out2.close();
	return seriesCount;
}
void mergeFiles(const char* file1, const char* file2, const char* outputFile) {
	ifstream f1(file1);
	ifstream f2(file2);
	ofstream out(outputFile);
	int val1, val2;
	int has1 = (f1 >> val1) ? 1 : 0;
	int has2 = (f2 >> val2) ? 1 : 0;
	while (has1 && has2) {
		if (val1 <= val2) {
			out << val1 << " ";
			has1 = (f1 >> val1) ? 1 : 0;
		}
		else {
			out << val2 << " ";
			has2 = (f2 >> val2) ? 1 : 0;
		}
	}
	while (has1) {
		out << val1 << " ";
		has1 = (f1 >> val1) ? 1 : 0;
	}
	while (has2) {
		out << val2 << " ";
		has2 = (f2 >> val2) ? 1 : 0;
	}
	f1.close();
	f2.close();
	out.close();
}
void naturalMergeSort(const char* inputFile, const char* outputFile) {
	const char* temp1 = "temp1.txt";
	const char* temp2 = "temp2.txt";
	const char* temp3 = "temp3.txt";
	int seriesCount = splitToSeries(inputFile, temp1, temp2);
	while (seriesCount > 1) {
		mergeFiles(temp1, temp2, temp3);
		seriesCount = splitToSeries(temp3, temp1, temp2);
	}
	ifstream in(temp1);
	ofstream out(outputFile);
	int val;
	while (in >> val) {
		out << val << " ";
	}
	in.close();
	out.close();
	remove(temp1);
	remove(temp2);
	remove(temp3);
}
void printFile(const char* filename) {
	ifstream file(filename);
	int val;
	while (file >> val) {
		cout << val << " ";
	}
	cout << endl;
	file.close();
}
int main() {
	setlocale(LC_ALL, "ru");
	ofstream f("input.txt");
	int arr[] = { 41, 8, 15, 24, 2, 1, 12, 7 };
	int n = sizeof(arr) / sizeof(arr[0]);
	for (int i = 0; i < n; i++) {
		f << arr[i] << " ";
	}
	f.close();
	cout << "Исходные данные: ";
	printFile("input.txt");
	naturalMergeSort("input.txt", "output.txt");
	cout << "Отсортированные данные: ";
	printFile("output.txt");
	return 0;
}